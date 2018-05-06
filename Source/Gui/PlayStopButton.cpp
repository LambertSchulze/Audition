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
PlayStopButton::PlayStopButton(String s)
:   ImageButton(s)
{
    this->setClickingTogglesState(true);
    this->setToggleState(false, dontSendNotification);
    
    playImage = ImageFileFormat::loadFrom(File("/Users/lambertschulze/Documents/Develop/Audition/Builds/MacOSX/svg/ic_add_black_48px.svg"));
    stopImage = ImageFileFormat::loadFrom(File("/Users/lambertschulze/Documents/Develop/Audition/Builds/MacOSX/svg/ic_stop_circle_outline_black_48px.svg"));
    
    this->setImages(true, true, true,
                    playImage, 0.7f, Colours::transparentBlack,
                    playImage, 1.0f, Colours::transparentBlack,
                    playImage, 1.0f, Colours::blue, 0.5f);
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
