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
    TransportManager (ValueTree& tree, AudioTransportSource& transportSource, GuiUI& gui);
    ~TransportManager ();
    
    //==============================================================================
    void changeListenerCallback (ChangeBroadcaster* thingThatChanged) override;
    void buttonClicked (Button* button) override;
    void stateChanged() override;
    void effectChanged() override;
    
    void setTransportSource ();
    
    OwnedArray<Effect> effectList;
    Effect* getEffectToPlay() const;
    
    static TransportManager* instance;

private:
    //==============================================================================
    ValueTree vt;
    
    AudioTransportSource& transportSource;
    GuiUI& ui;
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    
    Effect* effectToPlay = nullptr;
    
    void transportComponentClicked();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportManager)
};
