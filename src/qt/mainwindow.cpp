#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "MessageHandler.h"
#include <QDebug>
#include <QSerialPort>
#include "SerialPortSelector.h"

///////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow( parent ),
    ui_( new Ui::MainWindow ),
    serialPort_( nullptr )
{
    ui_->setupUi( this );
    MessageHandler::GetInstance().set_TextEdit( ui_->textEdit );

    serialPortSelector_ = new SerialPortSelector( *( ui_->menuSerial ) );
    connect( serialPortSelector_, SIGNAL( portNameChanged(QString) ), this, SLOT( onPortNameChanged(QString) ) );


}

///////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    delete serialPort_;
    delete serialPortSelector_;
    MessageHandler::GetInstance().set_TextEdit( nullptr );
    delete ui_;
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onPortNameChanged( QString newName )
{
    if( nullptr != serialPort_ )
    {
        qDebug( "Closing old serial port" );
        serialPort_->close();
        delete serialPort_;
    }

    serialPort_ = new QSerialPort( newName );

    if( !serialPort_->open( QIODevice::ReadWrite ) )
    {
        qWarning( "%s", QString("Failed opening serial port: " + newName).toStdString().c_str() );
        delete serialPort_;
        serialPort_ = nullptr;
    }
    else
    {
        qDebug( "%s", QString("Opened serial port: " + newName).toStdString().c_str() );
    }
}

///////////////////////////////////////////////////////////////////////////////
