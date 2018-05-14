/*
  ==============================================================================
    TransportComponent.h
    Created: 14 May 2018 12:28:13pm
    Author:  Lambert Schulze
  ==============================================================================
*/

#include "../JuceHeader.h"
#include "TransportComponentLookAndFeel.h"

class TransportComponent :  Component,
                            ValueTree::Listener
{
public:
    TransportComponent (ValueTree);
    
    ˜TransportComponent();
    
    void paint (Graphics);
    void resized ();
    
    void valueTreePropertyChanged (ValueTree&, const Identifier&);
    void valueTreeChildAdded (ValueTree&, ValueTree&);
    void valueTreeChildRemoved (ValueTree&, ValueTree&, int);
    void valueTreeChildOrderChanged (ValueTree&, int, int);
    void valueTreeParentChanged (ValueTree&);
    void valueTreeRedirected (ValueTree&);
    
    void originalButtonClicked();
    void effectButtonClicked();
    
public:
    ValueTree tree;
    TransportComponentLookAndFeel lookAndFeel;

    DrawableButton  OriginalButton, EffectButton;
    Label           InfoLabel;
    
    
}
