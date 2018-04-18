/*
  ==============================================================================

    LooseState.cpp
    Created: 21 Mar 2018 2:09:18pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "LooseState.h"
#include "../../Definitions/Definitions.h"

//==============================================================================
LooseState::LooseState(ValueTree& vt)
:   QuizState(vt)
{}

LooseState::~LooseState() {}

String LooseState::updateCounter() {return "Wrong!";}

void LooseState::setChoice(String) {}

void LooseState::next()
{
    newQuiz();
    deletePlayerChoice();
    
    quizNode.setProperty(IDs::QuizState, 0, nullptr);
}