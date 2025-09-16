#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SerialPortSelector;
class QSerialPort;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui_;
    SerialPortSelector* serialPortSelector_;
    QSerialPort* serialPort_;

private slots:
    void onPortNameChanged( QString newName );
};
#endif // MAINWINDOW_H
