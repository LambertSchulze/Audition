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
:   ShapeButton(s, Colours::grey, Colours::dimgrey, Colours::lightgrey)
{
    this->setClickingTogglesState(true);
    this->setToggleState(false, dontSendNotification);
    //this->setButtonText("Play");
    this->setShape(shape.playShape(), true, true, true);
}

PlayStopButton::~PlayStopButton() {}

void PlayStopButton::clicked()
{
    (this->getToggleState()) ? this->setButtonText("Stop") : this->setButtonText("Play");
    //std::cout << "Button: clicked()\n";
}

void PlayStopButton::setStateToOff()
{
    this->setToggleState(false, dontSendNotification);
    this->setButtonText("Play");
}
