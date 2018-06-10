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
#include "TransportState.h"
#include "GuiUI.h"

class TransportManager  : public TransportState,
                          public ChangeListener,
                          public Button::Listener
{
public:
    //==============================================================================
    TransportManager (AudioTransportSource& transportSource, GuiUI& gui);
    ~TransportManager ();
    
    //==============================================================================
    void changeListenerCallback (ChangeBroadcaster* thingThatChanged) override;
    void buttonClicked (Button* button) override;
    void stateChanged () override;
    void effectChanged () override;
    
    void setTransportSource ();
    
    Effect* getEffectToPlay() const;

private:
    //==============================================================================
    AudioTransportSource& transportSource;
    GuiUI& ui;
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    
    OwnedArray<Effect> effectList;
    Effect* effectToPlay = nullptr;
    
    void transportComponentClicked();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportManager)
};
