#include "Menu.h"

#include "TFT_eSPI.h"

///////////////////////////////////////////////////////////////////////////////

Menu::Menu( TFT_eSPI& tft ) :
    tft_( tft )
{
    initialise();
}

///////////////////////////////////////////////////////////////////////////////

void Menu::initialise()
{
    title_ = nullptr;

    for( int32_t i = 0U; i<MAX_OPTIONS; i++ )
    {
        setOption( i, nullptr, nullptr );
    }

    setBack( nullptr );
}

///////////////////////////////////////////////////////////////////////////////

void Menu::Start()
{
    tft_.setTextWrap( false, false );

    tft_.fillScreen( TFT_BLACK );
    tft_.setTextDatum( TL_DATUM );
    tft_.setTextWrap( false, false );

    tft_.setTextFont( 2 );
    tft_.setTextColor( TFT_WHITE );//, TFT_BLUE, true);

    tft_.fillRoundRect( 0, 0, tft_.width(), tft_.fontHeight() + 2, 4, TFT_BLUE );

    if( nullptr != title_ )
    {
        tft_.drawString( title_, 4, 1 );
    }

    for( int32_t i=0; i<MAX_OPTIONS; i++ )
    {
        if( nullptr != options_[i].text )
        {
            tft_.drawString( options_[i].text, OPT_TEXT_X_OFFSET, OPT_TEXT_Y_OFFSET + ( (i * tft_.fontHeight() ) + OPT_TEXT_LINE_SPACE ) );        
        }
    }

    tft_.setTextColor( TFT_LIGHTGREY );
    tft_.drawString( "BACK", OPT_TEXT_X_OFFSET, OPT_TEXT_Y_OFFSET + ( (MAX_OPTIONS * tft_.fontHeight() ) + OPT_TEXT_LINE_SPACE ) );

    highlighted_ = -1;
    down();
}

///////////////////////////////////////////////////////////////////////////////

void Menu::setTitle( const char *text )
{
    title_ = text;
}

///////////////////////////////////////////////////////////////////////////////

void Menu::setOption( const uint32_t optionNumber, const char* text, FuncPtr pFunc )
{
    if( optionNumber < MAX_OPTIONS )
    {
        options_[optionNumber].text = text;
        options_[optionNumber].pFunc = pFunc;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Menu::setBack( FuncPtr pFunc )
{
    pFunc_Back_ = pFunc;
}

///////////////////////////////////////////////////////////////////////////////

void Menu::up()
{
    if( highlighted_ > 0 )
    {
        const int32_t old = highlighted_;
        highlighted_--;

        while( ( highlighted_ >= 0 ) && ( options_[highlighted_].text == nullptr ) )
        {
            highlighted_--;
        }

        if( highlighted_ < 0 )
        {
            highlighted_ = old;
        }
        else
        {
            redrawSelected( old );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void Menu::down()
{
    if( highlighted_ < MAX_OPTIONS )
    {
        const int32_t old = highlighted_;
        highlighted_++;

        while( ( highlighted_ < MAX_OPTIONS ) && ( options_[highlighted_].text == nullptr ) )
        {
            highlighted_++;
        }

        redrawSelected( old );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Menu::enter()
{
    if( highlighted_ < MAX_OPTIONS )
    {    
        if( nullptr != options_[highlighted_].pFunc )
        {
            paintPush( highlighted_ );
            options_[highlighted_].pFunc();
        }
    }
    else
    {
        back();
    }
}

///////////////////////////////////////////////////////////////////////////////

void Menu::back()
{
    if( nullptr != pFunc_Back_ )
    { 
        paintPush( MAX_OPTIONS );
        pFunc_Back_();
    }
}

///////////////////////////////////////////////////////////////////////////////

void Menu::redrawSelected( const int32_t old )
{
    if( old >= 0 )
    {
        tft_.drawRoundRect( OPT_BOX_X_OFFSET, OPT_BOX_Y_OFFSET + ( ( old * tft_.fontHeight() ) + OPT_TEXT_LINE_SPACE ), tft_.width() - OPT_BOX_X_OFFSET, tft_.fontHeight() + 3, 4, TFT_BLACK );      
    }

    tft_.drawRoundRect( OPT_BOX_X_OFFSET, OPT_BOX_Y_OFFSET + ( ( highlighted_ * tft_.fontHeight() ) + OPT_TEXT_LINE_SPACE ), tft_.width() - OPT_BOX_X_OFFSET, tft_.fontHeight() + 3, 4, TFT_DARKGREY );      
}

///////////////////////////////////////////////////////////////////////////////

void Menu::paintPush( const int32_t option )
{
    const char* const text = ( option < MAX_OPTIONS ? options_[highlighted_].text : "BACK" );
    
    tft_.fillRoundRect( OPT_BOX_X_OFFSET, OPT_BOX_Y_OFFSET + ( ( option * tft_.fontHeight() ) + OPT_TEXT_LINE_SPACE ), tft_.width() - OPT_BOX_X_OFFSET, tft_.fontHeight() + 3, 4, TFT_DARKGREY );
    tft_.setTextColor( TFT_BLACK );
  
    tft_.drawString( text, OPT_TEXT_X_OFFSET, OPT_TEXT_Y_OFFSET + ( (option * tft_.fontHeight() ) + OPT_TEXT_LINE_SPACE ) );

    delay( 500 );
}