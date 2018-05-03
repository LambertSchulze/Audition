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
    return "Final Score:\nWon: " + quizNode.getProperty(IDs::WonRounds).toString() + "\nLost: " + quizNode.getProperty(IDs::LostRounds).toString();
}

void EndState::setChoice(String) {}

void EndState::next()
{
    newQuiz();
    deletePlayerChoice();
    
    // null other Parameters
    quizNode.setProperty(IDs::RoundCounter, 1, nullptr);
    quizNode.setProperty(IDs::WonRounds, 0, nullptr);
    quizNode.setProperty(IDs::LostRounds, 0, nullptr);
    
    quizNode.getParent().getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Stopping", nullptr);
    
    quizNode.getPropertyAsValue(IDs::QuizState, nullptr).setValue(0);
}
