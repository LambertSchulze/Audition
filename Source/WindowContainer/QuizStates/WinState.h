/*
  ==============================================================================

    WinState.h
    Created: 21 Mar 2018 2:09:08pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "QuizState.h"

//==============================================================================
/*
 */
class WinState : public QuizState
{
public:
    WinState        (ValueTree&);
    ~WinState       ();
    
    String updateCounter     ()          override;
    void setChoice  (String)    override;
    void next       ()          override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WinState)
};