/*
  ==============================================================================

    PlayStopButton.cpp
    Created: 21 Mar 2018 12:28:13pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PlayStopButton.h"
#include "../Core/Shapes.h"

//==============================================================================
PlayStopButton::PlayStopButton(String name)
:   ImageButton(name)
{
    this->setClickingTogglesState(true);
}

PlayStopButton::~PlayStopButton()
{
    
}

void PlayStopButton::paint (Graphics& g)
{
    bool isOn = this->getToggleState();
    auto b = getLocalBounds().toFloat();
    
    if (isOn) DrawShape::stop(g, b);
    else DrawShape::play(g, b);
    repaint();
}
