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
ControlComponent::ControlComponent(ValueTree& tree)
:   vt(tree),
    sourceComponent(vt),
    transportControl(vt)
{
    addAndMakeVisible(&sourceComponent);
    addAndMakeVisible(&transportControl);
    sourceComponent.updateSelection();
}

ControlComponent::~ControlComponent() {}

void ControlComponent::paint (Graphics& g) {}

void ControlComponent::resized()
{
    auto r          (getLocalBounds());
    auto footer     (r.removeFromBottom(UI::footerHeight));
    auto sidebar    (r.removeFromLeft(UI::sidebarWidth).withTrimmedTop(UI::headerHeight));
    
    sourceComponent .setBounds(sidebar);
    transportControl.setBounds(footer);
}
