/*
  ==============================================================================

    PlayStopButton.cpp
    Created: 21 Mar 2018 12:28:13pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PlayStopButton.h"

//==============================================================================
PlayStopButton::PlayStopButton(String name)
:   ImageButton(name)
{
    this->setClickingTogglesState(true);
    
    drawPlayImageOnButton();
}

PlayStopButton::~PlayStopButton()
{}

void PlayStopButton::clicked()
{
    auto b = this->getToggleState();
    
    if (b == true)  drawStopImageOnButton();
    else            drawPlayImageOnButton();
    
    repaint();
}

void PlayStopButton::drawStopImageOnButton()
{
    Image image (Image::RGB, 100, 100, true);
    
    Graphics s(image);
    s.setColour(Colours::black);
    s.fillEllipse(0, 0, 100, 100);
    s.setColour(Colours::lightgrey);
    s.fillRect(30, 30, 40, 40);
    
    this->setImages(false, true, true,
                    image, 0.7f, Colours::transparentBlack,
                    image, 1.0f, Colours::transparentBlack,
                    image, 1.0f, Colours::transparentBlack, 0.5);
}

void PlayStopButton::drawPlayImageOnButton()
{
    Image image (Image::RGB, 100, 100, true);
    
    Graphics p(image);
    p.setColour(Colours::black);
    p.fillEllipse(0, 0, 100, 100);
    p.setColour(Colours::lightgrey);
    p.drawArrow(Line<float>(25, 50, 75, 50), 0, 50, 50);
    
    this->setImages(false, true, true,
                    image, 0.7f, Colours::transparentBlack,
                    image, 1.0f, Colours::transparentBlack,
                    image, 1.0f, Colours::transparentBlack, 0.5);
}

void PlayStopButton::setStateToOff()
{
    this->setToggleState(false, dontSendNotification);
    this->clicked();
}
