/*
  ==============================================================================

    ChooseState.cpp
    Created: 21 Mar 2018 2:08:47pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "ChooseState.h"
#include "../../Definitions/Definitions.h"

//==============================================================================
ChooseState::ChooseState(ValueTree& vt)
:   QuizState(vt)
{}

ChooseState::~ChooseState() {}

String ChooseState::updateCounter()
{
    return "Listen and choose";
}

void ChooseState::setChoice(String choice)
{
    quizNode.setProperty(IDs::PlayerChoice, choice, nullptr);
}

void ChooseState::next()
{
    if (quizNode.getProperty(IDs::PlayerChoice) == quizNode.getChildWithProperty(IDs::isRight, true).getProperty(IDs::Name))
     {
         quizNode.setProperty(IDs::QuizState, 1, nullptr);
         quizNode.setProperty(IDs::WonRounds, (int) quizNode.getProperty(IDs::WonRounds) + 1, nullptr);
     }
     else
     {
         quizNode.setProperty(IDs::QuizState, 2, nullptr);
         quizNode.setProperty(IDs::LostRounds, (int) quizNode.getProperty(IDs::LostRounds) + 1, nullptr);
     }
}
