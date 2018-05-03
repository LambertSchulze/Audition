/*
  ==============================================================================

    ControlComponent.cpp
    Created: 18 Mar 2018 9:18:38pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "ControlComponent.h"
#include "../Definitions/Definitions.h"

//==============================================================================
ControlComponent::ControlComponent(ValueTree& vt)
:   tree(vt),
    sourceComponent(tree),
    transportControl(tree)
{
    addAndMakeVisible(&sourceComponent);
    addAndMakeVisible(&transportControl);
}

ControlComponent::~ControlComponent()
{}

void ControlComponent::paint (Graphics& g)
{}

void ControlComponent::resized()
{
    auto r          (getLocalBounds());
    auto footer     (r.removeFromBottom(UI::footerHeight));
    r.removeFromTop (UI::headerHeight);
    auto sidebar    (r.removeFromLeft(UI::sidebarWidth));
    
    sourceComponent .setBounds(sidebar);
    transportControl.setBounds(footer);
}
