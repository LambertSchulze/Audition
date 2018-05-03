/*
  ==============================================================================

    QuizState.h
    Created: 21 Mar 2018 2:07:50pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
class QuizState
{
public:
    QuizState               (ValueTree&);
    virtual ~QuizState      ();
    
    virtual String updateCounter     ();
    virtual void setChoice  (String);
    virtual void next       ();
    
    void newQuiz            ();
    void deletePlayerChoice ();
    
    ValueTree quizNode;
    
private:
    Random random;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuizState)
};