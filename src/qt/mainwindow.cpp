#include "mainwindow.h"
#include "Receiver.h"
#include "ui_mainwindow.h"

#include "MessageHandler.h"
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QTimer>
#include "PairedDeviceSelector.h"
#include "Scan.h"
#include "SerialPort.h"
#include "SerialPortSelector.h"

///////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow( parent ),
    Receiver(),
    ui_( new Ui::MainWindow ),
    file_( "comPort.txt" ),
    scan_( nullptr ),
    isOkay_( false )
{
    ui_->setupUi( this );
    ui_->menuPairing->setEnabled( false );
    ui_->slider_Quality->setEnabled( false );
    connect( ui_->slider_Quality, SIGNAL( valueChanged(int) ), this, SLOT( onAudioChanged(int) ) );

    QFont f = ui_->textEdit->font();
    f.setPointSize( 7 );
    ui_->textEdit->setFont( f );

    MessageHandler::GetInstance().set_TextEdit( ui_->textEdit );

    pairedDeviceSelector_ = new PairedDeviceSelector( *( ui_->menuPairing ) );
    connect( pairedDeviceSelector_, SIGNAL( deviceSelected(QString) ), this, SLOT( onDeviceSelected(QString) ) );

    serialPort2_ = nullptr;
    serialPortSelector_ = new SerialPortSelector( *( ui_->menuSerial ) );
    connect( serialPortSelector_, SIGNAL( portNameChanged(QString) ), this, SLOT( onPortNameChanged(QString) ) );
    connect( ui_->actionDelete_All, SIGNAL( triggered(bool) ), this, SLOT( onDeleteAll(bool) ) );
    connect( ui_->actionScan, SIGNAL( triggered(bool) ), this, SLOT( onScanRequest(bool) ) );

    connect( ui_->spinBox_A2DP, SIGNAL( valueChanged(int) ), this, SLOT( onChanged_A2DP_MicGain(int) ) );
    connect( ui_->spinBox_HFP, SIGNAL( valueChanged(int) ), this, SLOT( onChanged_HFP_MicGain(int) ) );

    ui_->spinBox_A2DP->setEnabled( false );
    ui_->spinBox_HFP->setEnabled( false );

    const bool exists = file_.exists();

    if( file_.open( QIODevice::ReadWrite | QIODevice::Text ) )
    {
        if( exists )
        {
            QTextStream in( &file_ );
            QString filename;
            in >> filename;

            if( !filename.isEmpty() )
            {
                onPortNameChanged( filename );
            }
        }
    }
    else
    {
        qWarning( "Couldn't open '%s'", file_.fileName().toStdString().c_str() );
    }
}

///////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    file_.close();
    delete serialPort2_;
    delete serialPortSelector_;
    delete pairedDeviceSelector_;
    MessageHandler::GetInstance().set_TextEdit( nullptr );
    delete ui_;
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onPortNameChanged( QString newName )
{
    if( nullptr != serialPort2_ )
    {
        delete serialPort2_;
    }

    serialPort2_ = new SerialPort( newName, *this );

    if( !serialPort2_->IsOpen() )
    {
        qWarning( "%s", QString("Failed opening serial port: " + newName).toStdString().c_str() );

        delete serialPort2_;
        serialPort2_ = nullptr;
    }
    else
    {
        file_.resize( 0 );
        QTextStream out( &file_ );
        out << newName;
        serialPortSelector_->overrideName( newName );

        transmit( "AT+NAME=Doctor Dongle,0" );
        transmit( "AT+A2DPSTAT" );
        transmit( "AT+HFPSTAT" );
        transmit( "AT+MICGAIN" );
        tranmsit( "AT+SPKVOL=15,15" );
        on_Audio_HiQ();
        refreshPairedList();
    }
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onDeleteAll( bool checked )
{
    Q_UNUSED( checked );

    const int ret = QMessageBox::warning(this, tr("Delete ALL"),
                                   tr("Do you want to delete ALL\n"
                                      "paired devices?"),
                                   QMessageBox::Ok | QMessageBox::Cancel );

    if( ret != QMessageBox::Cancel )
    {
        ui_->device_A2DP->setText( "" );
        ui_->device_HFP->setText( "" );

        transmit( "AT+PLIST=0" );
        transmit( "AT+REBOOT" );
        QTimer::singleShot( 5000, this, SLOT( refreshPairedList() ) );
    }
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::transmit( const char* c_str, const bool waitForOkay )
{
    if( nullptr != serialPort2_ )
    {
        serialPort2_->Transmit( c_str, waitForOkay );
    }
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::refreshPairedList()
{
    transmit( "AT+PLIST", false );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_OK()
{
    if( !isOkay_ )
    {
        isOkay_ = true;

        ui_->menuPairing->setEnabled( true );
        ui_->slider_Quality->setEnabled( true );
    }
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_A2DP_Connected( const bool isConnected )
{
    qWarning( "A2DP connected %d", static_cast<int>( isConnected ) );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_A2DP_Device( const std::string& deviceName )
{
    ui_->device_A2DP->setText( deviceName.c_str() );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_A2DP_MicGain( const int val )
{
    ui_->spinBox_A2DP->setValue( val );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_AUDROUTE( const std::string& val )
{
    qDebug( "    +AUDROUTE=%s", val.c_str() );

    if( val == "1" )
    {
        ui_->slider_Quality->setSliderPosition( 0 );

        ui_->spinBox_A2DP->setEnabled( true );
        ui_->spinBox_HFP->setEnabled( false );
    }
    else if( val == "2" )
    {
        ui_->slider_Quality->setSliderPosition( 1 );

        ui_->spinBox_A2DP->setEnabled( false );
        ui_->spinBox_HFP->setEnabled( true );
    }
    else
    {
        ui_->spinBox_A2DP->setEnabled( false );
        ui_->spinBox_HFP->setEnabled( false );
    }
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_HFP_Connected( const bool isConnected )
{
    qWarning( "HFP connected %d", static_cast<int>( isConnected ) );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_HFP_Device( const std::string& deviceName )
{
    ui_->device_HFP->setText( deviceName.c_str() );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_HFP_MicGain( const int val )
{
    ui_->spinBox_HFP->setValue( val );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_PairedList( const std::vector<Device>& deviceList )
{
    auto iter = deviceList.begin();

    while( iter != deviceList.end() )
    {
        qWarning( "PAIRED: %s %s", iter->name().c_str(), iter->macAddress().c_str() );
        ++iter;
    }

    pairedDeviceSelector_->onUpdatedList( deviceList );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_ScanList( const std::vector<Device>& deviceList )
{
    auto iter = deviceList.begin();

    while( iter != deviceList.end() )
    {
        qWarning( "SCANNED: %s %s", iter->name().c_str(), iter->macAddress().c_str() );
        ++iter;
    }

    if( nullptr != scan_ )
    {
        scan_->on_ScanList( deviceList );
    }
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_Audio_HiQ()
{
    transmit( "AT+AUDROUTE=1" );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_HeadSet_LoQ()
{
    transmit( "AT+AUDROUTE=2" );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onAudioChanged( int val )
{
    if( val == 0 )
    {
        on_Audio_HiQ();
    }
    else if( val == 1 )
    {
        on_HeadSet_LoQ();
    }
    else
    {
        ;   // do nothing
    }
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onScanRequest( bool checked )
{
    Q_UNUSED( checked );

    transmit( "AT+SCAN=1", false );

    scan_ = new Scan( this );
    connect( scan_, SIGNAL( deviceSelected(QString) ), this, SLOT( onDeviceSelected(QString) ) );

    scan_->exec();

    delete scan_;
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onDeviceSelected( QString macAddress )
{
    const QString connectStr = "AT+A2DPCONN=" + macAddress;

    transmit( "AT+AUDROUTE=0" );

    transmit( "AT+A2DPDISC" );
    transmit( "AT+HFPDISC" );
    ui_->device_A2DP->setText( "" );
    ui_->device_HFP->setText( "" );

    transmit( connectStr.toStdString().c_str() );
    transmit( "AT+AUDROUTE=1" );
    QTimer::singleShot( 5000, this, SLOT( refreshPairedList() ) );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onChanged_A2DP_MicGain( int val )
{
    const QString str = "AT+MICGAIN=" + QString::number( val ) + "," + QString::number( ui_->spinBox_HFP->value() );
    transmit( str.toStdString().c_str() );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onChanged_HFP_MicGain( int val )
{
    const QString str = "AT+MICGAIN=" + QString::number( ui_->spinBox_A2DP->value() ) + "," + QString::number( val );
    transmit( str.toStdString().c_str() );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::closeEvent( QCloseEvent *event )
{
    Q_UNUSED( event );

    transmit( "AT+REBOOT" );
    QThread::msleep( 1000 );
}

///////////////////////////////////////////////////////////////////////////////
