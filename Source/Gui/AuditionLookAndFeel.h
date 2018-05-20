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
                            black,                      // outline
                            black,                      // defaultText
                            yellow,                     // defaultFill (scrollbars)
                            white,                      // selected Button text
                            blue,                       // selected Button background
                            red
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
    
    Colour  black       {0, 0, 0},
            grey        {142, 142, 145},
            lightergrey {205, 205, 208},
            lightgrey   {242, 242, 245},
            white       {255, 255, 255},
            blue        {27, 173, 248},
            brown       {162, 132, 94},
            green       {99, 218, 56},
            orange      {255, 149, 0},
            pink        {255, 41, 104},
            purple      {204, 115, 225},
            red         {255, 59, 48},
            yellow      {255, 204, 0};

};

#endif
