#include "AuditionLookAndFeel.h"


AuditionLookAndFeel::AuditionLookAndFeel()
{
    auto colourScheme = Desktop::isOSXDarkModeActive() ? getDarkColourScheme() : getLightColourScheme();
    setColourScheme(colourScheme);
}
