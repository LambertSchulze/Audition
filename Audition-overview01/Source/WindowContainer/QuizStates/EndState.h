/*
  ==============================================================================

    EndState.h
    Created: 21 Mar 2018 5:03:23pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "QuizState.h"

//==============================================================================
/*
 */
class EndState : public QuizState
{
public:
    EndState        (ValueTree&);
    ~EndState       ();
    
    String updateCounter     ()          override;
    
    void setChoice  (String)    override;
    void next       ()          override;
    
private:    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EndState)
};