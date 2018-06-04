/*
 ==============================================================================
 
 GuiManager.h
 Created: 4 Jun 2018 9:32:08pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TransportManager.h"

class GuiManager  : public Button::Listener,
                           ChangeListener
{
public:
    GuiManager (TransportManager& tm);
    ~GuiManager ();
    
    void buttonClicked (Button* button) override;
    void buttonStateChanged (Button* button) override;
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
private:
    TransportManager& transport;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiManager)
};
