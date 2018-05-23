/*
  ==============================================================================

    PlayStopButton.h
    Created: 21 Mar 2018 12:28:13pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Definitions.h"

//==============================================================================
/*
 */
class PlayStopButton :  public ImageButton,
                        public ValueTree::Listener
{
public:
    PlayStopButton(String, ValueTree&);
    ~PlayStopButton();
    
    void clicked() override;
    
    //==============================================================================
    void valueTreePropertyChanged (ValueTree&, const Identifier&) override;
    void valueTreeChildAdded (ValueTree&, ValueTree&) override;
    void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override;
    void valueTreeChildOrderChanged (ValueTree&, int, int) override;
    void valueTreeParentChanged (ValueTree&) override;
    void valueTreeRedirected (ValueTree&) override;

    //==============================================================================
    void setStateToOff();
    
private:
    ValueTree vt;
    
    void drawPlayImageOnButton();
    void drawStopImageOnButton();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayStopButton)
};
