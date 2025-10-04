#include "mainwindow.h"
#include "Commander.h"
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

    commander_ = new Commander;
    receiver_ = new Receiver( *this );

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
    delete commander_;
    delete serialPort2_;
    delete serialPortSelector_;
    delete pairedDeviceSelector_;
    delete receiver_;
    MessageHandler::GetInstance().set_TextEdit( nullptr );
    delete ui_;
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onPortNameChanged( QString newName )
{
    if( nullptr != serialPort2_ )
    {
        commander_->clr_RequiredIf();
        delete serialPort2_;
    }

    serialPort2_ = new SerialPort( newName, *receiver_ );

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

        commander_->set_RequiredIf( *serialPort2_ );
        commander_->defaults();
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

        commander_->clr_PLIST();
        commander_->reboot();
        QTimer::singleShot( 5000, this, SLOT( refresh() ) );
    }
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::refresh()
{
    commander_->defaults();
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

void MainWindow::on_AUDROUTE( const int val )
{
    qDebug( "    +AUDROUTE=%d", val );

    if( val == 1 )
    {
        ui_->slider_Quality->setSliderPosition( 0 );

        ui_->spinBox_A2DP->setEnabled( true );
        ui_->spinBox_HFP->setEnabled( false );
    }
    else if( val == 2 )
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
    commander_->set_AUDROUTE__A2DP();
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_HeadSet_LoQ()
{
    commander_->set_AUDROUTE__HFP();
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

    scan_ = new Scan( this );
    connect( scan_, SIGNAL( deviceSelected(QString) ), this, SLOT( onDeviceSelected(QString) ) );

    commander_->req_SCAN();
    scan_->exec();

    delete scan_;
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onDeviceSelected( QString macAddress )
{
    commander_->disconnect();
    ui_->device_A2DP->setText( "" );
    ui_->device_HFP->setText( "" );
    commander_->pair( macAddress.toStdString().c_str() );

    QTimer::singleShot( 5000, this, SLOT( refresh() ) );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onChanged_A2DP_MicGain( int val )
{
    commander_->set_MICGAIN(val, ui_->spinBox_HFP->value() );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::onChanged_HFP_MicGain( int val )
{
    commander_->set_MICGAIN( ui_->spinBox_A2DP->value(), val );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::closeEvent( QCloseEvent *event )
{
    Q_UNUSED( event );

    commander_->reboot();
    QThread::msleep( 1000 );
}

///////////////////////////////////////////////////////////////////////////////
