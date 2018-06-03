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

class TransportComponent :  public  Component,
                                    ValueTree::Listener
{
public:
    TransportComponent (ValueTree&);
    
    ~TransportComponent();
    
    //==============================================================================
    enum State {Disabled, OriginalEnabled, BothEnabled} state;
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized () override;
    
    //==============================================================================
    void valueTreePropertyChanged (ValueTree&, const Identifier&) override;
    void valueTreeChildAdded (ValueTree&, ValueTree&) override;
    void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override;
    void valueTreeChildOrderChanged (ValueTree&, int, int) override;
    void valueTreeParentChanged (ValueTree&) override;
    void valueTreeRedirected (ValueTree&) override;
    
    void mouseDown (const MouseEvent&) override;
    void originalButtonClicked();
    void effectButtonClicked();
    
    void setState (State&);
    
private:
    ValueTree vt;
    TransportComponentLookAndFeel lookAndFeel;
    
    bool labelShowingOriginal;
    
    void switchLabelText (bool);
    void updateState();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportComponent)
};
