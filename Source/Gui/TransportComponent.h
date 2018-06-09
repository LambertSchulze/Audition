/*
  ==============================================================================
    TransportComponent.h
    Created: 14 May 2018 12:28:13pm
    Author:  Lambert Schulze
  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TransportComponentLookAndFeel.h"
#include "../Definitions/Definitions.h"

class TransportComponent  : public Component,
                            public ChangeBroadcaster
{
public:
    TransportComponent (String name);
    
    ~TransportComponent();
    
    //==============================================================================
    enum ComponentState {Disabled = 0, OriginalEnabled = 1, BothEnabled = 2} componentState = Disabled;
    enum ButtonState {NoButtonPressed = 0, OriginalButtonPressed = 1, EffectButtonPressed = 2} buttonState = NoButtonPressed;
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized () override;
    
    //==============================================================================    
    void mouseDown (const MouseEvent&) override;
    void originalButtonClicked(bool dontSendNotification = false);
    void effectButtonClicked();
    
    void setComponentState (ComponentState& newState);
    void setComponentState (int newState);
    
    void setButtonState (ButtonState& newState);
    void setButtonState (int newState);
    ButtonState getButtonState() const;
    int getButtonStateAsInt() const;
    bool noButtonPressed() const;
    
    bool inOriginalMode() const;
    bool inEffectMode() const;
    
    void turnBothPlayButtonsOff();
    
private:
    TransportComponentLookAndFeel lookAndFeel;
    
    bool originalHeadPressed = false, effectHeadPressed = false;
    bool labelShowingOriginal = true;
    
    void switchLabelText (bool);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportComponent)
};
