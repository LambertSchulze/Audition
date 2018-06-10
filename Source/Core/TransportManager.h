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
#include "GuiUI.h"

enum TransportState {STARTING, PLAYING, STOPPING, STOPPED};

class TransportManager  : public ChangeListener,
                          public Button::Listener
{
public:
    //==============================================================================
    TransportManager (AudioTransportSource& transportSource, GuiUI& gui);
    ~TransportManager ();
    
    //==============================================================================
    void changeListenerCallback (ChangeBroadcaster* thingThatChanged) override;
    void buttonClicked (Button* button) override;

    void setTransportSource ();
    
    void setTransportTo (const TransportState& transportState);
    TransportState getTransportState();
    
    void setEffectPlayback (bool shouldPlayEffect);
    bool shouldPlayEffect() const;
    
    void setPlaybackFile (const String& filePath);
    String getPlaybackFile();
    void setStartTime (int newStartTime);
    
    void setEffectToPlay (int effectNumberToPlay);
    Effect* getEffectToPlay() const;
    
    void startPlayingOriginal (const String& filePath, const int& startTime);
    void startPlayingWithEffect (const String& filePath, const int& startTime, Effect* effectToPlay);
    void stopPlayback();

private:
    //==============================================================================
    AudioTransportSource& transportSource;
    GuiUI& ui;
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    
    OwnedArray<Effect> effectList;
    Effect* effectToPlay = nullptr;
    
    TransportState transportState {STOPPED};
    bool isPlayingEffect = false;
    String playbackFile = "";
    int startTime = 0;
    
    void transportComponentClicked();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportManager)
};
