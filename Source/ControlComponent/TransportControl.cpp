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
    originalButton("Original"), effectButton("Effect"),
    originalLabel("Original"), effectLabel("Effect")
{    
    addAndMakeVisible(&originalButton);
    addAndMakeVisible(&effectButton);
    addAndMakeVisible(&originalLabel);
    addAndMakeVisible(&effectLabel);
    
    originalButton  .setClickingTogglesState(true);
    effectButton    .setClickingTogglesState(true);
    
    originalLabel   .setText("Original", dontSendNotification);
    originalLabel   .setJustificationType(Justification::centred);
    effectLabel     .setText("Effect", dontSendNotification);
    effectLabel     .setJustificationType(Justification::centred);
    
    // originalButton should only be enabled if Filelist is not empty and a file is selected.
    // effectButton should only be enabled if a file is loaded and a effect for playback is set.
    // this has to be checked in the beginning and after every change of the properties.
    
    if (mainVT.getChildWithName(IDs::FileList).getNumChildren() == 0) originalButton.setEnabled(false);
    
    // the effect button is always disabled in the beginning.
    effectButton.setEnabled(false);

    originalButton.onClick = [this] { originalButtonclicked(); };
    effectButton.onClick   = [this] { effectButtonclicked(); };
    mainVT          .addListener(this);
}

TransportControl::~TransportControl()
{
    mainVT          .removeListener(this);
}

void TransportControl::paint (Graphics& g)      {}

void TransportControl::resized()
{
    auto r (getLocalBounds());
    auto l (r.removeFromLeft(r.getWidth() / 2));
    l = l.removeFromRight(100).reduced(10);
    r = r.removeFromLeft(100).reduced(10);
    
    originalButton  .setBounds(l.removeFromTop(50));
    originalLabel   .setBounds(l);
    effectButton    .setBounds(r.removeFromTop(50));
    effectLabel     .setBounds(r);
}

//==============================================================================
void TransportControl::valueTreePropertyChanged (ValueTree& changedTree, const Identifier& property)
{
    // disabling buttons in different QuizStates
    if (property == IDs::QuizState)
    {
        if ((int) changedTree.getProperty(property) == 3)
        {
            originalButton  .setEnabled(false);
            effectButton    .setEnabled(false);
        }
        if ((int) changedTree.getProperty(property) == 0)
        {
            originalButton  .setEnabled(true);
            effectButton    .setEnabled(true);
        }
    }
    
    // if no effect is set for playback, that means, Effect_To_Play has the value -1 (like at startup),
    // the effect button is dissabled. Otherwise its being enabled.
    if (property == IDs::EffectToPlay) {((int) changedTree.getProperty(property) == -1) ? effectButton.setEnabled(false) : effectButton.setEnabled(true);}
    
    // if playback stopps by removing the file from the list, the buttons must get untoggled
    if (property == IDs::TransportState)
    {
        // if transportState is Stopping or Stopped, untoggle Buttons
        if ((String) changedTree.getProperty(property) == "Stopping")
    }
}

void TransportControl::valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded)
{
    // makes shure that buttons get enabled if files are in the filelist.
    
    if (parentTree.hasType(IDs::FileList))
    {
        originalButton  .setEnabled(true);
    }
}

void TransportControl::valueTreeChildRemoved (ValueTree &parentTree, ValueTree &childWhichHasBeenRemoved, int /*index*/)
{
    // if all files of the filelist are removed, disables buttons
    
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
void TransportControl::originalButtonclicked()
{
    DBG("originalButton: clicked");
    if (originalButton.getToggleState())
    {
        mainVT.getChildWithName(IDs::Transport).setProperty(IDs::IsProcessing, false, nullptr);
        mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Starting", nullptr);
        effectButton.setToggleState(false, dontSendNotification);
    }
    else
    {
        mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Stopping", nullptr);
    }
}

void TransportControl::effectButtonclicked()
{
    DBG("effectButton: clicked");
    if (effectButton.getToggleState())
    {
        mainVT.getChildWithName(IDs::Transport).setProperty(IDs::IsProcessing, true, nullptr);
        mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Starting", nullptr);
        originalButton.setToggleState(false, dontSendNotification);
    }
    else
    {
        mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Stopping", nullptr);
    }
}
