/*
 ==============================================================================
 
 AudioComponent.h
 Created: 18 Mar 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "Definitions/Definitions.h"
#include "Gui/Gui.h"
#include "Core/TransportManager.h"
#include "Core/FileManager.h"

class MainContentComponent   :  public AudioAppComponent
{
public:
    //==============================================================================
    MainContentComponent(ValueTree& vt);
    ~MainContentComponent();
    
    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    //==============================================================================
    void resized() override;
    
private:
    //==============================================================================
    ValueTree tree;
    Gui gui;
    AudioTransportSource transportSource;
    TransportManager transport;
    FileManager fileManager;
    
    friend Gui;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
