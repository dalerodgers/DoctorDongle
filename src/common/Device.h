#ifndef Device_H
#define Device_H

#include <string>

class Device
{
public:
    Device( const std::string& name, const std::string& macAddress ) :
        name_( name),
        macAddress_( macAddress )
    {
        // do nothing
    }

    inline const std::string& name() const
    {
        return name_;
    }

    inline const std::string& macAddress() const
    {
        return macAddress_;
    }

private:
    const std::string name_;
    const std::string macAddress_;
};

#endif // Device_H
