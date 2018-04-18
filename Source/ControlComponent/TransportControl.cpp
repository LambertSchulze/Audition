/*
  ==============================================================================

    TransportControl.cpp
    Created: 18 Mar 2018 9:19:16pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TransportControl.h"
#include "../Definitions/Definitions.h"

//==============================================================================
TransportControl::TransportControl (ValueTree& vt)
:   mainVT(vt),
    originalButton("Original"), effectButton("Effect")
{    
    addAndMakeVisible(&originalButton);
    addAndMakeVisible(&effectButton);
    originalButton  .setClickingTogglesState(true);
    effectButton    .setClickingTogglesState(true);
    effectButton    .setEnabled(false);
    
    originalButton  .addListener(this);
    effectButton    .addListener(this);
    
    
    mainVT.addListener(this);
}

TransportControl::~TransportControl()
{
    originalButton  .removeListener(this);
    effectButton    .removeListener(this);
    mainVT          .removeListener(this);
}

void TransportControl::paint (Graphics& g)      {}

void TransportControl::resized()
{
    auto r (getLocalBounds());
    r.removeFromLeft(10);
    originalButton  .setBounds(r.removeFromLeft(100).reduced(10));
    effectButton    .setBounds(r.removeFromLeft(100).reduced(10));
    originalButton  .setCentreRelative(0.4, 0.5);
    effectButton    .setCentreRelative(0.6, 0.5);
}

//==============================================================================
void TransportControl::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    if (property == IDs::QuizState)
    {
        if ((int) treeWhosePropertyHasChanged.getProperty(property) == 3)
        {
            originalButton  .setEnabled(false);
            effectButton    .setEnabled(false);
        }
        if ((int) treeWhosePropertyHasChanged.getProperty(property) == 0)
        {
            originalButton  .setEnabled(true);
            effectButton    .setEnabled(true);
        }
    }
    
    if (property == IDs::forPlayback && (bool) treeWhosePropertyHasChanged.getProperty(property) == true) effectButton.setEnabled(true);
}

void TransportControl::valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded)
{
    if (parentTree.hasType(IDs::FileList))
    {
        originalButton  .setEnabled(true);
        effectButton    .setEnabled(true);
    }
}

void TransportControl::valueTreeChildRemoved (ValueTree &parentTree, ValueTree &childWhichHasBeenRemoved, int /*index*/)
{
    if (parentTree.hasType(IDs::FileList))
    {
        if (parentTree.getNumChildren() == 0)
        {
            originalButton  .setEnabled(false);
            effectButton    .setEnabled(false);
        }
    }
}

void TransportControl::valueTreeChildOrderChanged (ValueTree&, int, int) {}
void TransportControl::valueTreeParentChanged (ValueTree&) {}
void TransportControl::valueTreeRedirected (ValueTree&) {}

//==============================================================================
void TransportControl::buttonClicked(Button* b)
{
    if (b == &originalButton)
    {
        if (originalButton.getToggleState())
        {
            mainVT.getChildWithName(IDs::Transport).setProperty(IDs::IsProcessing, false, nullptr);
            mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Starting", nullptr);
            effectButton.setStateToOff();
            //std::cout << "OB: getToggleState() true\n";
        }
        else
        {
            mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Stopping", nullptr);
            //std::cout << "OB: getToggleState() else\n";
        }
    }
    if (b == &effectButton)
    {
        if (effectButton.getToggleState())
        {
            mainVT.getChildWithName(IDs::Transport).setProperty(IDs::IsProcessing, true, nullptr);
            mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Starting", nullptr);
            originalButton.setStateToOff();
            //std::cout << "EB: getToggleState() true\n";
        }
        else
        {
            mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Stopping", nullptr);
            //std::cout << "EB: getToggleState() else\n";
        }
    }
}
