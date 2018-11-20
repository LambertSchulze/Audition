/*
 ==============================================================================
 
 NextButtonLookAndFeel.h
 Created: 13 Apr 2018 8:51:56pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Definitions.h"

class NextButtonLookAndFeel : public LookAndFeel_V4
{
public:
    NextButtonLookAndFeel()
    {
        setColour(TextButton::ColourIds::buttonColourId, Colours::transparentWhite);
        setColour(TextButton::ColourIds::textColourOffId, AuditionColours::blue);
    }
    
    ~NextButtonLookAndFeel()
    {
        
    }
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        Rectangle<float> buttonArea = button.getLocalBounds().toFloat();
        const int outlineThickness = 2;
        const int cornerSize = buttonArea.getHeight() / 2;
    
        //draw outline
        auto colour = (button.isEnabled()) ?
            AuditionColours::blue : AuditionColours::blue.withMultipliedAlpha(0.4);
        g.setColour (colour);
        g.drawRoundedRectangle(buttonArea.reduced(outlineThickness/2), cornerSize, outlineThickness);
        //fill background
        g.setColour (backgroundColour);
        g.fillRoundedRectangle(buttonArea.reduced(outlineThickness/2), cornerSize);
    };
    
};
