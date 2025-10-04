#include "Receiver.h"

///////////////////////////////////////////////////////////////////////////////

Receiver::Receiver( RequiredIf& requiredIf ) :
    requiredIf_( requiredIf )
{
    a2dp_isConnected_ = false;
    hfp_isConnected_ = false;

    pairedList_.clear();
    scanList_.clear();
}

///////////////////////////////////////////////////////////////////////////////

Receiver::~Receiver()
{
    // do nothing
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::OnReponse( const std::string& str )
{
    if( str == "OK" )
    {
        requiredIf_.on_OK();
    }
    else if( str.find( "ERR" ) == 0U )
    {
        requiredIf_.on_ERR();
    }
    else
    {
        std::vector<std::string> list;
        split( str.c_str(), '=', list );

        if( list.size() == 2 )
        {
            if( list.at(0).compare("+A2DPDEV") == 0 )
            {
                parse_A2DPDEV( list.at(1) );
            }
            else if( list.at(0).compare("+A2DPSTAT") == 0 )
            {
                parse_A2DPSTAT( list.at(1) );
            }
            else if( list.at(0).compare("+AUDMODE") == 0 )
            {
                parse_AUDMODE( list.at(1) );
            }
            else if( list.at(0).compare("+AUDROUTE") == 0 )
            {
                parse_AUDROUTE( list.at(1) );
            }
            else if( list.at(0).compare("+HFPDEV") == 0 )
            {
                parse_HFPDEV( list.at(1) );
            }
            else if( list.at(0).compare("+HFPSTAT") == 0 )
            {
                parse_HFPSTAT( list.at(1) );
            }
            else if( list.at(0).compare("+MICGAIN") == 0 )
            {
                parse_MICGAIN( list.at(1) );
            }
            else if( list.at(0).compare("+PLIST") == 0 )
            {
                parse_PLIST( list.at(1) );
            }
            else if( list.at(0).compare("+SCAN") == 0 )
            {
                parse_SCAN( list.at(1) );
            }
            else
            {
                ;   // do nothing
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::split(const std::string& str, char separator, std::vector<std::string>& dst )
{
    std::string::size_type startIndex = 0;
    std::string::size_type endIndex = 0;

    for ( std::string::size_type i = 0; i <= str.size(); i++ )
    {
        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size())
        {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            dst.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::parse_A2DPDEV( const std::string& val )
{
    std::vector<std::string> vals;
    split( val, ',', vals );

    if( vals.size() == 2U )
    {
        requiredIf_.on_A2DP_Device( vals.at(1) );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::parse_A2DPSTAT( const std::string& val )
{
    std::vector<std::string> vals;
    split( val, ',', vals );

    if( vals.size() == 1U )
    {
        const int status = std::stoi( vals.at(0) ); // get param1
        bool new_a2dp_isConnected = false;

        if( ( status >= 3 ) && ( status <= 5 ) )
        {
            new_a2dp_isConnected = true;
        }

        if( a2dp_isConnected_ != new_a2dp_isConnected )
        {
            a2dp_isConnected_ = new_a2dp_isConnected;
            requiredIf_.on_A2DP_Connected( a2dp_isConnected_ );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::parse_HFPDEV( const std::string& val )
{
    std::vector<std::string> vals;
    split( val, ',', vals );

    if( vals.size() == 2U )
    {
        requiredIf_.on_HFP_Device( vals.at(1) );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::parse_HFPSTAT( const std::string& val )
{
    std::vector<std::string> vals;
    split( val, ',', vals );

    if( vals.size() >= 1U )
    {
        const int status = std::stoi( vals.at(0) ); // get param1
        bool new_hfp_isConnected = false;

        if( ( status >= 3) && ( status <= 10 ) )
        {
            new_hfp_isConnected = true;
        }

        if( hfp_isConnected_ != new_hfp_isConnected )
        {
            hfp_isConnected_ = new_hfp_isConnected;
            requiredIf_.on_HFP_Connected( hfp_isConnected_ );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::parse_MICGAIN( const std::string& val )
{
    std::vector<std::string> vals;
    split( val, ',', vals );

    if( vals.size() == 2U )
    {
        requiredIf_.on_A2DP_MicGain( atoi( vals.at(0).c_str() ) );
        requiredIf_.on_HFP_MicGain( atoi( vals.at(1).c_str() ) );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::parse_AUDMODE( const std::string& val )
{
    const int numeric = std::stoi( val );
    requiredIf_.on_AUDMODE( numeric );
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::parse_AUDROUTE( const std::string& val )
{
    const int numeric = std::stoi( val );
    requiredIf_.on_AUDROUTE( numeric );
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::parse_PLIST( const std::string& val )
{
    std::vector<std::string> vals;
    split( val, ',', vals );

    if( vals.size() == 4U )
    {
        pairedList_.push_back( Device( vals.at(3), vals.at(2) ) );
    }
    else if( ( vals.size() == 1U ) && vals.at(0).at(0) == 'E' )
    {
        requiredIf_.on_PairedList( pairedList_ );    // end of PLIST report received
        pairedList_.clear();
    }
    else
    {
        ;   // do nothing
    }
}

///////////////////////////////////////////////////////////////////////////////

void Receiver::parse_SCAN( const std::string& val )
{
    std::vector<std::string> vals;
    split( val, ',', vals );

    if( vals.size() == 6U )
    {
        scanList_.push_back( Device( vals.at(4), vals.at(3) ) );
    }
    else if( ( vals.size() == 1U ) && vals.at(0).at(0) == 'E' )
    {
        requiredIf_.on_ScanList( scanList_ );    // end of SCAN report received
        scanList_.clear();
    }
    else
    {
        ;   // do nothing
    }
}

///////////////////////////////////////////////////////////////////////////////
