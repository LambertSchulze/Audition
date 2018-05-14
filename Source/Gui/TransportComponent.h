/*
  ==============================================================================
    TransportComponent.h
    Created: 14 May 2018 12:28:13pm
    Author:  Lambert Schulze
  ==============================================================================
*/

#include "../JuceHeader.h"
#include "TransportComponentLookAndFeel.h"
#include "../Definitions/Definitions.h"

class TransportComponent :  Component,
                            ValueTree::Listener
{
public:
    TransportComponent (ValueTree&);
    
    ~TransportComponent();
    
    void paint (Graphics);
    void resized ();
    
    void valueTreePropertyChanged (ValueTree&, const Identifier&) override;
    void valueTreeChildAdded (ValueTree&, ValueTree&) override;
    void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override;
    void valueTreeChildOrderChanged (ValueTree&, int, int) override;
    void valueTreeParentChanged (ValueTree&) override;
    void valueTreeRedirected (ValueTree&) override;
    
    void originalButtonClicked();
    void effectButtonClicked();
    
    void setupChildComponents();
    void setupShape();
    
public:
    ValueTree tree;
    TransportComponentLookAndFeel lookAndFeel;

    ShapeButton     OriginalButton, EffectButton;
    Label           InfoLabel;
    
    
};
