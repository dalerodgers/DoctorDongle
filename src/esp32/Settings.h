#include <Preferences.h>

class Settings
{
public:
    static void load();
    static void save();

    static void flipOff();
    static void flipOn();
    static bool flipped();

private:
    static Preferences preferences_;
    static bool flipped_;
};