#ifndef SerialComms_H
#define SerialComms_H

#include <list>
#include <string>
#include "src/common/Commander.h"
#include "src/common/Receiver.h"

class SerialComms : public Commander::RequiredIf
{
public:
    SerialComms( Receiver& receiver );

    void initialise();
    void loop();

    virtual void Transmit( const char* c_str, const bool waitForOkay = true ) override;

private:
    struct Waiter
    {
        const std::string str;
        const bool waitForOkay;
    };

    Receiver& receiver_;
    std::string buffer_;

    std::list<Waiter> waiters_;
    bool waitingForOkay_;
    unsigned long waitingForOkayTimeStart_;

    void checkList();
};

#endif