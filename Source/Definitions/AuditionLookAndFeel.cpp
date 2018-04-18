/*
 ==============================================================================
 
 AuditionLookAndFeel.h
 Created: 12 Apr 2018 8:51:56pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#ifndef __AuditionLookAndFeel__
#define __AuditionLookAndFeel__

#include "../../JuceLibraryCode/JuceHeader.h"

class AuditionLookAndFeel :     public LookAndFeel_V4
{
public:
    AuditionLookAndFeel ()
    {
        setColourScheme({   Colours::transparentWhite,  // windowBackground
                            Colours::transparentWhite,  // widgetBackground
                            Colours::transparentWhite,  // menuBackground
                            Colours::blue,              // outline
                            Colours::pink,              // defaultText
                            Colours::yellow,            // defaultFill (scrollbars)
                            Colours::cornsilk,
                            Colours::coral,
                            Colours::rosybrown
                        });
        /*
         windowBackground       0xffefefef
         widgetBackground       0xffffffff
         menuBackground         0xffffffff
         outline                0xffdddddd
         defaultText            0xff000000
         defaultFill            0xffa9a9a9
         highlightedText        0xffffffff
         highlightedFill        0xff42a2c8
         menuText               0xff000000
         numColours
         */
        
        
    };

};

#endif