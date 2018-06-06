/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainContentComponent.h"
#include "Definitions/Definitions.h"

//==============================================================================
MainContentComponent::MainContentComponent(ValueTree& vt)
:   tree(vt), gui(vt), transport(transportSource), fileManager(vt, gui, transport)
{
    setAudioChannels (0, 2);
    
    if (effectList.isEmpty()) {
        effectList.add(new NoEffect());
        effectList.add(new SumVolumeUp());
        effectList.add(new SumVolumeDown());
        effectList.add(new LeftSolo());
        effectList.add(new RightSolo());
        effectList.add(new Mono());
        effectList.add(new LRSwitched());
        effectList.add(new MidVolumeUp());
        effectList.add(new MidVolumeDown());
        effectList.add(new SideVolumeUp());
        effectList.add(new SideVolumeDown());
    }
    
    addAndMakeVisible(gui);
    setSize(tree.getProperty(IDs::WindowWidth), tree.getProperty(IDs::WindowHeight));
    
    gui.hoockToParentObjects(); // This function adds Button::Listeners and the TableListBoxModel to the Gui.
                                // It gets called now because it uses getParentComponent() wich only returns
                                // true if the Component is already added.
}

MainContentComponent::~MainContentComponent()
{
    transportSource.setSource(nullptr);
    shutdownAudio();
}

void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock (bufferToFill);
    
    transportSource.setGain(Decibels::decibelsToGain(-3));

    if (transport.shouldPlayEffect()) {
        transport.getEffectToPlay();
    }
}

void MainContentComponent::releaseResources()
{
    transportSource.releaseResources();
}

void MainContentComponent::resized()
{
    gui.setBounds(getLocalBounds());
    
    tree.setProperty(IDs::WindowHeight, this->getHeight(), nullptr);
    tree.setProperty(IDs::WindowWidth, this->getWidth(), nullptr);
}
