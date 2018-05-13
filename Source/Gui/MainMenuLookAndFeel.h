/*
 ==============================================================================
 
 MainMenueLookAndFeel.h
 Created: 13 May 2018 8:51:56pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "AuditionLookAndFeel.h"

class MainMenuLookAndFeel :     public LookAndFeel_V4
{
public:
    MainMenuLookAndFeel()
    : bgColour1 (laf.orange), bgColour2 (laf.red)
    {
        setColour(TextButton::ColourIds::buttonColourId, Colours::transparentWhite);
        setColour(TextButton::ColourIds::buttonOnColourId, laf.white);
        setColour(TextButton::ColourIds::textColourOffId, laf.white);
        setColour(TextButton::ColourIds::textColourOnId, laf.blue);
    };
    
    ~MainMenuLookAndFeel()
    {
        
    };
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                                      bool isMouseOverButton, bool isButtonDown) override
    {
        Rectangle<float> buttonArea = button.getLocalBounds().toFloat();
        int cornerSize          = 16;
        int outlineThickness    = 4;
        
        if (isButtonDown) {
            g.setColour(laf.white.withAlpha(0.8f));
            g.fillRoundedRectangle(buttonArea.reduced(outlineThickness/2), cornerSize);
        }
        
        else {
        //draw outline
        g.setColour (laf.white);
        g.drawRoundedRectangle(buttonArea.reduced(outlineThickness/2), cornerSize, outlineThickness);
        //fill background
        g.setColour (backgroundColour);
        g.fillRoundedRectangle(buttonArea.reduced(outlineThickness/2), cornerSize);
        }
    };
    
    AuditionLookAndFeel laf;
    
    Colour  bgColour1, bgColour2;
};
