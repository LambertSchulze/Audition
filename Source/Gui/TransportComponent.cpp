/*
  ==============================================================================
    TransportComponent.cpp
    Created: 14 May 2018 12:28:13pm
    Author:  Lambert Schulze
  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TransportComponent.cpp"

//==============================================================================
TransportComponent::TransportComponent(ValueTree vt)
:   tree(vt),
    originalButton("Original Button"), effectButton("Effect Button"),
    infoLabel("TransportComponent Label")
{
    addAndMakeVisible(&originalButton);
    addAndMakeVisible(&effectButton);
    addAndMakeVisible(&
}
