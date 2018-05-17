/*
  ==============================================================================

    TransportControl.h
    Created: 18 Mar 2018 9:19:16pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Gui/TransportLookAndFeel.h"
#include "../Gui/TransportComponentLookAndFeel.h"
#include "../Gui/PlayStopButton.h"
#include "../Gui/TransportComponent.h"

//==============================================================================
/*
*/
class TransportControl :    public Component,
                            public ValueTree::Listener
{
public:
    TransportControl(ValueTree&);
    ~TransportControl();

    void paint (Graphics&) override;
    void resized() override;
    
    void valueTreePropertyChanged (ValueTree&, const Identifier&) override;
    void valueTreeChildAdded (ValueTree&, ValueTree&) override;
    void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override;
    void valueTreeChildOrderChanged (ValueTree&, int, int) override;
    void valueTreeParentChanged (ValueTree&) override;
    void valueTreeRedirected (ValueTree&) override;
    
    void shuffleButtonclicked();
    void repeatButtonclicked();
    void autostopButtonclicked();
    void originalButtonclicked();
    void effectButtonclicked();
    
private:
    ValueTree vt;
    TransportLookAndFeel lookAndFeel;
    TransportComponentLookAndFeel tcLookAndFeel;
    
    DrawableButton shuffleButton, repeatButton, autostopButton;
    PlayStopButton originalButton, effectButton;
    Label originalLabel, effectLabel;
    TransportComponent transport;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportControl)
};
