/*
 ==============================================================================
 
 TransportManager.h
 Created: 1 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Effects.h"

enum TransportState {STARTING, PLAYING, STOPPING, STOPPED};

class TransportManager  : public ChangeListener
{
public:
    //==============================================================================
    TransportManager (AudioTransportSource& transportSource);
    ~TransportManager ();
    
    //==============================================================================
    void changeListenerCallback (ChangeBroadcaster* thingThatChanged) override;
    
    void setTransportTo (const TransportState& transportState);
    void setEffectPlayback (bool shouldPlayEffect);
    void setEffectToPlay (Effect* effectToPlay);
    void setFileForPlayback (String& filePath);
    void setStartPosition (int newStartTime);
    
    Effect* getEffectToPlay();
    bool shouldPlayEffect();
    
    void startPlayingOriginal();
    void startPlayingWithEffect (Effect* effectToPlay);
    void stopPlayback();
    
private:
    //==============================================================================
    AudioTransportSource& transportSource;
    AudioFormatManager formatManager;
    TransportState transportState {STOPPED};
    bool isPlayingEffect = false;
    Effect* effectToPlay = nullptr;
    int startTime = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportManager)
};
