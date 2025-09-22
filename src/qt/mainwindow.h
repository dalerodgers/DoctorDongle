#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Receiver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PairedDeviceSelector;
class Scan;
class SerialPort;
class SerialPortSelector;
class QSerialPort;

class MainWindow : public QMainWindow, Receiver
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void on_OK() override;
    virtual void on_ERR() override {}

    virtual void on_A2DP_Connected( const bool isConnected ) override;
    virtual void on_A2DP_Device( const std::string& deviceName ) override;
    virtual void on_A2DP_MicGain( const int val ) override;
    virtual void on_AUDROUTE( const std::string& val ) override;
    virtual void on_HFP_Connected( const bool isConnected ) override;
    virtual void on_HFP_Device( const std::string& deviceName ) override;
    virtual void on_HFP_MicGain( const int val ) override;
    virtual void on_PairedList( const std::vector<Device>& deviceList ) override;
    virtual void on_ScanList( const std::vector<Device>& deviceList ) override;

    virtual void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui_;
    PairedDeviceSelector* pairedDeviceSelector_;
    SerialPort* serialPort2_;
    SerialPortSelector* serialPortSelector_;

    Scan* scan_;
    QSerialPort* serialPort_;
    bool isOkay_;

    void transmit( const char* c_str, const bool waitForOkay = true );

    void on_Audio_HiQ();
    void on_HeadSet_LoQ();

private slots:
    void onPortNameChanged( QString newName );
    void onDeleteAll( bool checked );

    void onAudioChanged( int val );

    void onScanRequest( bool checked );
    void onDeviceSelected( QString macAddress );

    void onChanged_A2DP_MicGain( int val );
    void onChanged_HFP_MicGain( int val );

    void refreshPairedList();
};
#endif // MAINWINDOW_H
