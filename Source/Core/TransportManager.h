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

class TransportManager  : public ChangeListener,
                          public Button::Listener
{
public:
    //==============================================================================
    TransportManager (AudioTransportSource& transportSource);
    ~TransportManager ();
    
    //==============================================================================
    void changeListenerCallback (ChangeBroadcaster* thingThatChanged) override;
    void buttonClicked (Button* button) override;
    
    void setTransportSource ();
    void setTransportTo (const TransportState& transportState);
    void setEffectPlayback (bool shouldPlayEffect);
    void setEffectToPlay (Effect* effectToPlay);
    void setPlaybackFile (const String& filePath);
    void setStartTime (int newStartTime);
    
    Effect* getEffectToPlay() const;
    bool shouldPlayEffect() const;
    
    void startPlayingOriginal (const String& filePath, const int& startTime);
    void startPlayingWithEffect (const String& filePath, const int& startTime, Effect* effectToPlay);
    void stopPlayback();
    
private:
    //==============================================================================
    AudioTransportSource& transportSource;
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    
    TransportState transportState {STOPPED};
    bool isPlayingEffect = false;
    Effect* effectToPlay = nullptr;
    String playbackFile = "";
    int startTime = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportManager)
};
