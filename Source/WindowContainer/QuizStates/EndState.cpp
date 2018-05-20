/*
  ==============================================================================

    EndState.cpp
    Created: 21 Mar 2018 5:03:23pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "EndState.h"
#include "../../Definitions/Definitions.h"

//==============================================================================
EndState::EndState(ValueTree& vt)
:   QuizState(vt)
{}

EndState::~EndState() {}

String EndState::updateCounter()
{
    return "Final Score:\nWon: " + QUIZ.getProperty(IDs::WonRounds).toString() + "\nLost: " + QUIZ.getProperty(IDs::LostRounds).toString();
}

void EndState::setChoice(String) {}

void EndState::next()
{
    newQuiz();
    deletePlayerChoice();
    
    // null other Parameters
    QUIZ.setProperty(IDs::RoundCounter, 1, nullptr);
    QUIZ.setProperty(IDs::WonRounds, 0, nullptr);
    QUIZ.setProperty(IDs::LostRounds, 0, nullptr);
    
    TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
    
    QUIZ.getPropertyAsValue(IDs::QuizState, nullptr).setValue(0);
}
