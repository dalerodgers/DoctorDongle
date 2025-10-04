#ifndef Menu_H
#define Menu_H

#include <stdint.h>

class TFT_eSPI;

class Menu
{
public:
    typedef void (*FuncPtr)();
    static constexpr int32_t MAX_OPTIONS = 4U;

    Menu( TFT_eSPI& tft );

    void initialise();
    virtual void Start() = 0;

    void setTitle( const char* text );
    void setOption( const uint32_t optionNumber, const char* text, FuncPtr pFunc = nullptr );
    void setBack( FuncPtr pFunc );

    void up();
    void down();
    void enter();
    void back();

private:
    static constexpr int32_t OPT_TEXT_X_OFFSET = 12;
    static constexpr int32_t OPT_TEXT_Y_OFFSET = 17;
    static constexpr int32_t OPT_TEXT_LINE_SPACE = 7;

    static constexpr int32_t OPT_BOX_X_OFFSET = 8;
    static constexpr int32_t OPT_BOX_Y_OFFSET = 15;

    struct Option
    {
        const char* text;
        FuncPtr pFunc;
    };

    TFT_eSPI& tft_;

    const char* title_;
    Option options_[MAX_OPTIONS];
    FuncPtr pFunc_Back_;    
    int32_t highlighted_;

    void redrawSelected( const int32_t old );
    void paintPush( const int32_t option );
};

#endif