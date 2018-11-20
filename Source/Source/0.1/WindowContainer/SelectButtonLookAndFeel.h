/*
 ==============================================================================
 
 SelectButtonLookAndFeel.h
 Created: 13 Apr 2018 8:51:56pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Definitions.h"

class SelectButtonLookAndFeel : public LookAndFeel_V4
{
public:
    SelectButtonLookAndFeel()
    {
        setColour(TextButton::ColourIds::buttonColourId, AuditionColours::white);
        setColour(TextButton::ColourIds::buttonOnColourId, AuditionColours::blue);
        setColour(TextButton::ColourIds::textColourOffId, AuditionColours::black);
        setColour(TextButton::ColourIds::textColourOnId, AuditionColours::white);
    }
    
    ~SelectButtonLookAndFeel()
    {
        
    }
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        Rectangle<float> buttonArea = button.getLocalBounds().toFloat();
        const int outlineThickness = 2;
        
        if (isMouseOverButton) {
//            const auto shadowColour = Colours::grey.withMultipliedAlpha(0.1);
//            Colour gradientColour = Colours::transparentBlack;
//
//            auto top = button.getLocalBounds().removeFromTop(radius).withTrimmedLeft(radius).withTrimmedRight(radius);
//            auto topG = ColourGradient(shadowColour, top.getX(), top.getBottom(), gradientColour, top.getX(), top.getY(), false);
//            g.setGradientFill(topG);
//            g.fillRect(top);
//            auto bottom = button.getLocalBounds().removeFromBottom(radius).withTrimmedLeft(radius).withTrimmedRight(radius);
//            auto bottomG = ColourGradient(shadowColour, bottom.getX(), bottom.getY(), gradientColour, bottom.getX(), bottom.getBottom(), false);
//            g.setGradientFill(bottomG);
//            g.fillRect(bottom);
//            auto left = button.getLocalBounds().removeFromLeft(radius).withTrimmedTop(radius).withTrimmedBottom(radius);
//            auto leftG = ColourGradient(shadowColour, left.getWidth(), left.getY(), gradientColour, left.getX(), left.getY(), false);
//            g.setGradientFill(leftG);
//            g.fillRect(left);
//            auto right = button.getLocalBounds().removeFromRight(radius).withTrimmedTop(radius).withTrimmedBottom(radius);
//            auto rightG = ColourGradient(shadowColour, right.getX(), right.getY(), gradientColour, right.getWidth(), right.getY(), false);
//            g.setGradientFill(rightG);
//            g.fillRect(right);
//
//            auto topLeft = button.getLocalBounds().removeFromTop(radius).removeFromLeft(radius);
//            auto topLeftG = ColourGradient(shadowColour, topLeft.getWidth(), topLeft.getHeight(), gradientColour, topLeft.getX(), topLeft.getHeight(), true);
//            g.setGradientFill(topLeftG);
//            g.fillRect(topLeft);
//            auto topRight = button.getLocalBounds().removeFromTop(radius).removeFromRight(radius);
//            auto topRightG = ColourGradient(shadowColour, topRight.getX(), topRight.getHeight(), gradientColour, topRight.getWidth(), topRight.getHeight(), true);
//            g.setGradientFill(topRightG);
//            g.fillRect(topRight);
//            auto bottomLeft = button.getLocalBounds().removeFromBottom(radius).removeFromLeft(radius);
//            auto bottomLeftG = ColourGradient(shadowColour, bottomLeft.getWidth(), bottomLeft.getY(), gradientColour, bottomLeft.getX(), bottomLeft.getY(), true);
//            g.setGradientFill(bottomLeftG);
//            g.fillRect(bottomLeft);
//            auto bottomRight = button.getLocalBounds().removeFromBottom(radius).removeFromRight(radius);
//            auto bottomRightG = ColourGradient(shadowColour, bottomRight.getX(), bottomRight.getY(), gradientColour, bottomRight.getWidth(), bottomRight.getY(), true);
//            g.setGradientFill(bottomRightG);
//            g.fillRect(bottomRight);
            
            auto ds = DropShadow(Colours::lightgrey.withMultipliedAlpha(0.3), 1, Point<int>(0, 2));
            ds.drawForRectangle(g, buttonArea.toNearestInt());
        }
        
        {
            //draw outline
            g.setColour (AuditionColours::lightgrey);
            g.drawRect(buttonArea.reduced(outlineThickness/2), outlineThickness);
            //fill background
            auto colour = (isButtonDown) ?
                AuditionColours::blue.withMultipliedAlpha(0.08) : backgroundColour;
            g.setColour (colour);
            g.fillRect(buttonArea.reduced(outlineThickness));
        }
    };
    
};
