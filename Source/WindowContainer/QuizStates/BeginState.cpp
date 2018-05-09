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
    QUIZ.setProperty(IDs::RoundCounter, 1, nullptr);
    QUIZ.setProperty(IDs::WonRounds, 0, nullptr);
    QUIZ.setProperty(IDs::LostRounds, 0, nullptr);
    
    TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
    
    QUIZ.setProperty(IDs::QuizState, 0, nullptr);
}
