#include "SerialPort.h"

#include <QSerialPort>
#include <QString>
#include <QTimer>
#include "Receiver.h"

///////////////////////////////////////////////////////////////////////////////

SerialPort::SerialPort( const QString& name, Receiver& receiver ) :
    name_( name ),
    receiver_( receiver ),
    mutex_()
{
    qSerialPort_ = new QSerialPort( name );
    waitingForOkay_ = false;

    if( !qSerialPort_->open( QIODevice::ReadWrite ) )
    {
        qWarning( "%s", QString("Failed opening serial port: " + name).toStdString().c_str() );
        qSerialPort_->close();

        delete qSerialPort_;
        qSerialPort_ = nullptr;
    }
    else
    {
        qDebug( "%s", QString("Opened serial port: " + name).toStdString().c_str() );

        qSerialPort_->setBaudRate( 115200U );
        qSerialPort_->setParity( QSerialPort::Parity::NoParity );
        qSerialPort_->setStopBits( QSerialPort::StopBits::OneStop );

        connect( qSerialPort_, SIGNAL( readyRead() ), this, SLOT( onReadyRead() ) );
    }
}

///////////////////////////////////////////////////////////////////////////////

SerialPort::~SerialPort()
{
    if( nullptr != qSerialPort_ )
    {
        qSerialPort_->close();
        delete qSerialPort_;
    }
}

///////////////////////////////////////////////////////////////////////////////

void SerialPort::Transmit( const char* c_str, const bool waitForOkay )
{
    if( nullptr != qSerialPort_ )
    {
        mutex_.lock();

        waiters_.push_back( Waiter( { c_str, waitForOkay } ) );
        checkList();

        mutex_.unlock();
    }
}

///////////////////////////////////////////////////////////////////////////////

bool SerialPort::IsOpen() const
{
    return static_cast<bool>( nullptr != qSerialPort_ );
}

///////////////////////////////////////////////////////////////////////////////

void SerialPort::onReadyRead()
{
    if( nullptr != qSerialPort_ )
    {
        while( qSerialPort_->canReadLine() )
        {
            QByteArray line = qSerialPort_->readLine();
            line = line.trimmed();

            if( line.size() > 0 )
            {
                qDebug( "%s", QString( "Rx: " + line ).toStdString().c_str() );

                if( !waitingForOkay_ )
                {
                    ;   // do nothing
                }
                else if( "OK" != line )
                {
                    ;   // do nothing
                }
                else
                {
                    mutex_.lock();

                    waitingForOkay_ = false;
                    checkList();

                    mutex_.unlock();
                }

                receiver_.OnReponse( line.toStdString() );
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void SerialPort::onTimeout()
{
    mutex_.lock();

    waitingForOkay_ = false;
    checkList();

    mutex_.unlock();
}

///////////////////////////////////////////////////////////////////////////////

void SerialPort::checkList()
{
    while( !waitingForOkay_ && !waiters_.empty() )
    {
        const QString str = waiters_.begin()->str;

        qDebug( "%s", QString( "Tx: " + str ).toStdString().c_str() );
        qSerialPort_->write( QString( str + "\r\n" ).toStdString().c_str() );

        if( waiters_.begin()->waitForOkay )
        {
            waitingForOkay_ = true;
            QTimer::singleShot( 500, this, SLOT( onTimeout() ) );
        }

        waiters_.pop_front();
    }
}

///////////////////////////////////////////////////////////////////////////////
