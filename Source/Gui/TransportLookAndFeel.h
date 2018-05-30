/*
 ==============================================================================
 
 TransportLookAndFeel.h
 Created: 13 May 2018 8:51:56pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "AuditionLookAndFeel.h"

class TransportLookAndFeel :    public LookAndFeel_V4
{
public:
    TransportLookAndFeel ()
    {
        //setColour(DrawableButton::backgroundColourId, Colours::pink);
        //setColour(DrawableButton::backgroundOnColourId, Colours::green);
    };
    
    void drawDrawableButton (Graphics& g, DrawableButton&, bool, bool ) override
    {
        g.fillAll (laf.lightergrey);
    };
    
    ~TransportLookAndFeel () {};
    
    AuditionLookAndFeel laf;
};
