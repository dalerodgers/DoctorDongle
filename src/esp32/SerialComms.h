#ifndef SerialComms_H
#define SerialComms_H

#include "src/common/Receiver.h"

class SerialComms
{
public:
    SerialComms( Receiver& receiver );

    void initialise();
    void loop();

private:
    Receiver& receiver_;
};

#endif