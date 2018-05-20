/*
  ==============================================================================

    LooseState.h
    Created: 21 Mar 2018 2:09:18pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "QuizState.h"

//==============================================================================
/*
 */
class LooseState : public QuizState
{
public:
    LooseState      (ValueTree&);
    ~LooseState     ();
    
    String updateCounter     ()          override;
    void setChoice  (String)    override;
    void next       ()          override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LooseState)
};