#ifndef Receiver_H
#define Receiver_H

#include "Device.h"
#include <string>
#include <vector>

class Receiver
{
public:
    class RequiredIf
    {
    public:
        virtual void on_OK() = 0;
        virtual void on_ERR() = 0;

        virtual void on_A2DP_Connected( const bool isConnected ) = 0;
        virtual void on_A2DP_Device( const std::string& deviceName ) = 0;
        virtual void on_A2DP_MicGain( const int val ) = 0;
        virtual void on_AUDMODE( const int val ) = 0;
        virtual void on_AUDROUTE( const int val ) = 0;
        virtual void on_HFP_Connected( const bool isConnected ) = 0;
        virtual void on_HFP_Device( const std::string& deviceName ) = 0;
        virtual void on_HFP_MicGain( const int val ) = 0;
        virtual void on_PairedList( const std::vector<Device>& deviceList ) = 0;
        virtual void on_ScanList( const std::vector<Device>& deviceList ) = 0;
    };

    Receiver( RequiredIf& requiredIf );
    ~Receiver();

    void OnReponse( const std::string& str );

    static void split( const std::string& str, char separator, std::vector<std::string>& dst );

private:
    RequiredIf& requiredIf_;

    bool a2dp_isConnected_;
    bool hfp_isConnected_;

    std::vector<Device> pairedList_;
    std::vector<Device> scanList_;

    void parse_A2DPDEV( const std::string& val );
    void parse_A2DPSTAT( const std::string& val );
    void parse_HFPDEV( const std::string& val );
    void parse_HFPSTAT( const std::string& val );
    void parse_MICGAIN( const std::string& val );
    void parse_AUDMODE( const std::string& val );
    void parse_AUDROUTE( const std::string& val );
    void parse_PLIST( const std::string& val );
    void parse_SCAN( const std::string& val );
};

#endif // Receiver_H
