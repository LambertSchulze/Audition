/*
  ==============================================================================

    OverviewScreen.cpp
    Created: 18 Mar 2018 9:32:33pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "OverviewScreen.h"

//==============================================================================
OverviewScreen::OverviewScreen(ValueTree& vt)
:   mainVT(vt)
{

}

OverviewScreen::~OverviewScreen()
{
}

void OverviewScreen::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("OverviewScreen", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void OverviewScreen::resized()
{

}
