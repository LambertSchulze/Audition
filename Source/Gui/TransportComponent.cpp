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
TransportComponent::TransportComponent(ValueTree& vt)
:   tree(vt),
    originalButton("Original Button"), effectButton("Effect Button"),
    infoLabel("TransportComponent Label")
{      
    
}

TransportComponent::~TransportComponent()
{}

void TransportComponent::paint(Graphics& g)
{}

void TransportComponent::resized()
{
    auto r (getLocalBounds());
    
    originalButton.setBounds();
    effectButton  .setBounds();
    infoLabel     .setBounds();
}

void TransportComponent::valueTreePropertyChanged (ValueTree& changedTree, const Identifier& property) {}
void TransportComponent::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childTree) {}
void TransportComponent::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childTree, int index) {}
void TransportComponentvalueTreeChildOrderChanged (ValueTree& parentTree, int oldIndex, int newIndex) {}
void TransportComponent::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) {}
void TransportComponent::valueTreeRedirected (ValueTree& treeWhichHasBeenChanged) {}

void TransportComponent::originalButtonClicked()
{
    DBG("Play Original Button clicked");  
}

void TransportComponent::effectButtonClicked()
{
    DBG("Play Effect Button clicked");  
}

void TransportComponent::setupChildComponents()
{
    // all the setup of the Buttons and Label
    addAndMakeVisible(&originalButton);
    addAndMakeVisible(&effectButton);
    addAndMakeVisible(&infoLabel);
    
    originalButton  .setLookAndFeel(&lookAndFeel);
    effectButton    .setLookAndFeel(&lookAndFeel);
    infoLabel       .setLookAndFeel(&lookAndFeel);
  
    originalButton  .setClickingTogglesState(true);
    effectButton    .setClickingTogglesState(true);
    
    originalButton.onClick() = [this] { originalButtonClicked(); };
    effectButton  .onClick() = [this] { effectButtonClicked(); };
}

void TransportComponent::setupShape()
{
    // some painting and additional Button setup
    Image canvas(PixelFormat::RGB, 100, 100, true);
    Graphics g(canvas);
  
    g.setColour(Colours::black),
    g.drawEllipse(0, 0, 100, 100);
}
