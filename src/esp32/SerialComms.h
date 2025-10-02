#ifndef SerialComms_H
#define SerialComms_H

#include <string>
#include "src/common/Receiver.h"

class SerialComms
{
public:
    SerialComms( Receiver& receiver );

    void initialise();
    void loop();

private:
    Receiver& receiver_;
    std::string buffer_;
};

#endif