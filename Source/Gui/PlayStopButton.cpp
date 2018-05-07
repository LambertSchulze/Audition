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
    this->setToggleState(false, dontSendNotification);
    
    //playImage = ImageFileFormat::loadFrom(File("/Users/lambertschulze/Documents/Develop/Audition/Builds/MacOSX/svg/ic_add_black_48px.svg"));
    //stopImage = ImageFileFormat::loadFrom(File("/Users/lambertschulze/Documents/Develop/Audition/Builds/MacOSX/svg/ic_stop_circle_outline_black_48px.svg"));
    
    Image playImage (Image::RGB, 100, 100, true);
    Image stopImage (Image::RGB, 100, 100, true);
    
    Graphics p(playImage);
    p.setColour(Colours::black);
    p.fillEllipse(0, 0, 100, 100);
    p.setColour(Colours::green);
    p.drawArrow(Line<float>(25, 50, 75, 50), 0, 50, 100);
    
    Graphics s(stopImage);
    s.setColour(Colours::black);
    s.fillEllipse(0, 0, 100, 100);
    s.setColour(Colours::red);
    s.fillRect(25, 25, 50, 50);
    
    this->setImages(true, true, true,
                    playImage, 0.7f, Colours::transparentBlack,
                    playImage, 1.0f, Colours::transparentBlack,
                    stopImage, 1.0f, Colours::transparentBlack, 0.5);
}

PlayStopButton::~PlayStopButton() {}

void PlayStopButton::clicked()
{
    (this->getToggleState()) ? this->setButtonText("Stop") : this->setButtonText("Play");
    //DBG("PlayStopButton: clicked()");
}

void PlayStopButton::setStateToOff()
{
    this->setToggleState(false, dontSendNotification);
    this->setButtonText("Play");
}
