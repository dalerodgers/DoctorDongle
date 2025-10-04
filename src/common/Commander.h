#ifndef Commander_H
#define Commander_H

class Commander
{
public:
    class RequiredIf
    {
    public:
        virtual void Transmit( const char* c_str, const bool waitForOkay = true ) = 0;
    };

    Commander();

    void clr_RequiredIf();
    void set_RequiredIf( RequiredIf& requiredIf );

    void defaults();
    void reboot();

    void pair( const char* macAddress );
    void disconnect();

    void set_NAME();
    void get_A2DPSTAT();
    void get_HFPSTAT();
    void get_MICGAIN();
    void set_MICGAIN( int a2dp, int hfp );
    void set_SPKVOL();
    void clr_PLIST();
    void req_PLIST();
    void set_AUDROUTE__A2DP();
    void set_AUDROUTE__HFP();
    void set_AUDROUTE__None();
    void req_SCAN();
    void get_VER();

private:
    RequiredIf* requiredIf_;
};

#endif
