/*
  ==============================================================================

    PlayStopButton.h
    Created: 21 Mar 2018 12:28:13pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Shapes.h"

//==============================================================================
/*
 */
class PlayStopButton :  public ShapeButton
{
public:
    PlayStopButton(String);
    ~PlayStopButton();
    
    void clicked() override;
    
    void setStateToOff();
    
private:
    Shapes shape;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayStopButton)
};
