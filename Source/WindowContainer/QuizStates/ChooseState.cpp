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
    QUIZ.setProperty(IDs::PlayerChoice, choice, nullptr);
}

void ChooseState::next()
{
    if (QUIZ.getProperty(IDs::PlayerChoice) == QUIZ.getChildWithProperty(IDs::isRight, true).getProperty(IDs::Name))
     {
         QUIZ.setProperty(IDs::QuizState, 1, nullptr);
         QUIZ.setProperty(IDs::WonRounds, (int) QUIZ.getProperty(IDs::WonRounds) + 1, nullptr);
     }
     else
     {
         QUIZ.setProperty(IDs::QuizState, 2, nullptr);
         QUIZ.setProperty(IDs::LostRounds, (int) QUIZ.getProperty(IDs::LostRounds) + 1, nullptr);
     }
}
