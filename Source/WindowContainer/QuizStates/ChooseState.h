/*
  ==============================================================================

    ChooseState.h
    Created: 21 Mar 2018 2:08:47pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "QuizState.h"

//==============================================================================
/*
 */
class ChooseState : public QuizState
{
public:
    ChooseState     (ValueTree&);
    ~ChooseState    ();
    
    String updateCounter     ()   override;
    void setChoice  (String)    override;
    void next       ()          override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChooseState)
};