/*
 ==============================================================================
 
 BeginState.cpp
 Created: 4 Apr 2018 5:03:23pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "BeginState.h"
#include "../../Definitions/Definitions.h"

//==============================================================================
BeginState::BeginState(ValueTree& vt)
:   QuizState(vt)
{}

BeginState::~BeginState() {}

String BeginState::updateCounter()      {return "Begin";}

void BeginState::setChoice(String) {}

void BeginState::next()
{
    newQuiz();
    deletePlayerChoice();
    
    // null other Parameters
    quizNode.setProperty(IDs::RoundCounter, 1, nullptr);
    quizNode.setProperty(IDs::WonRounds, 0, nullptr);
    quizNode.setProperty(IDs::LostRounds, 0, nullptr);
    
    quizNode.getParent().getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Stopping", nullptr);
    
    quizNode.setProperty(IDs::QuizState, 0, nullptr);
}
