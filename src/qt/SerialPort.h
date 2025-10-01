#ifndef SerialPort_H
#define SerialPort_H

#include "Commander.h"
#include <list>
#include <QMutex>
#include <QObject>
#include <string>

class QSerialPort;
class Receiver;

class SerialPort : public QObject, public Commander::RequiredIf
{
    Q_OBJECT

public:
    SerialPort( const QString& name, Receiver& receiver );
    ~SerialPort();

    virtual void Transmit( const char* c_str, const bool waitForOkay ) override;
    bool IsOpen() const;

private:
    struct Waiter
    {
        const QString str;
        const bool waitForOkay;
    };

    const QString& name_;
    Receiver& receiver_;
    QMutex mutex_;
    QSerialPort* qSerialPort_;

    std::list<Waiter> waiters_;
    volatile bool waitingForOkay_;

    void checkList();

private slots:
    void onReadyRead();
    void onTimeout();
};

#endif // SerialPort_H
