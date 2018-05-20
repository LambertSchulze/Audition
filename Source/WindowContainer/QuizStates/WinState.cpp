/*
  ==============================================================================

    WinState.cpp
    Created: 21 Mar 2018 2:09:08pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "WinState.h"
#include "../../Definitions/Definitions.h"

//==============================================================================
WinState::WinState(ValueTree& vt)
:   QuizState(vt)
{}

WinState::~WinState() {}

String WinState::updateCounter() {return "That was right!";}

void WinState::setChoice(String) {}

void WinState::next()
{
    newQuiz();
    deletePlayerChoice();
    
    QUIZ.setProperty(IDs::QuizState, 0, nullptr);
}
