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
:   tree(vt), gui(vt), transport(vt, transportSource, gui), fileManager(vt, gui)
{
    setAudioChannels (0, 2);
        
    addAndMakeVisible(gui);
    setSize(tree.getProperty(IDs::WindowWidth), tree.getProperty(IDs::WindowHeight));
    
    gui.Register(); // This function adds Button::Listeners and the TableListBoxModel to the Gui.
                    // It gets called now because it uses getParentComponent() wich only returns
                    // true if the Component is already added.
    
    gui.fileList.selectRow(0); // now we can default select a row in fileList
}

MainContentComponent::~MainContentComponent()
{
    transportSource.setSource(nullptr);
    shutdownAudio();
}

void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
    
    if (transport.getEffectToPlay()) {
        transport.getEffectToPlay()->prepareToPlay(samplesPerBlockExpected, sampleRate);
    }
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock (bufferToFill);
    
    transportSource.setGain(Decibels::decibelsToGain(-3));

    if (transport.getEffectToPlay()) {
        transport.getEffectToPlay()->processEffect(bufferToFill);
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
