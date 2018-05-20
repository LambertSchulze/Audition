/*
  ==============================================================================

    QuizState.cpp
    Created: 21 Mar 2018 2:07:50pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "QuizState.h"
#include "../../Definitions/Definitions.h"

//==============================================================================
QuizState::QuizState (ValueTree& tree)
:   vt(tree)
{}

QuizState::~QuizState()
{}

String QuizState::updateCounter     ()          {return "";}
void QuizState::setChoice           (String)    {}
void QuizState::next                ()          {}

void QuizState::newQuiz             ()
{
    // get 3 random Effects of the List of all Effects
    
    int numOfAllEffects     = EFFECTLIST.getNumChildren();
    
    int randEffect1         = random.nextInt(numOfAllEffects);
    
    int randEffect2         = random.nextInt(numOfAllEffects);
    
    int randEffect3         = random.nextInt(numOfAllEffects);
 
    QUIZ.getChild(0).setProperty(IDs::Name, EFFECTLIST.getChild(randEffect1).getProperty(IDs::EffectName), nullptr);
    QUIZ.getChild(1).setProperty(IDs::Name, EFFECTLIST.getChild(randEffect2).getProperty(IDs::EffectName), nullptr);
    QUIZ.getChild(2).setProperty(IDs::Name, EFFECTLIST.getChild(randEffect3).getProperty(IDs::EffectName), nullptr);
    
    // set one of them as the right one
    
    if (QUIZ.getChildWithProperty(IDs::isRight, true).isValid()) QUIZ.getChildWithProperty(IDs::isRight, true).setProperty(IDs::isRight, false, nullptr);
    if (EFFECTLIST.getChildWithProperty(IDs::forPlayback, true).isValid()) EFFECTLIST.getChildWithProperty(IDs::forPlayback, true).setProperty(IDs::forPlayback, false, nullptr);
    
    int rightAnswer = random.nextInt(3);
    
    QUIZ.getChild(rightAnswer).setProperty(IDs::isRight, true, nullptr);
    
    EFFECTLIST.getChildWithProperty(IDs::EffectName, QUIZ.getChildWithProperty(IDs::isRight, true).getProperty(IDs::Name)).setProperty(IDs::forPlayback, true, nullptr);

//    std::cout << "right Answer: " << quizNode.getChild(rightAnswer).getProperty(IDs::Name).toString() << "\n";
}

void QuizState::deletePlayerChoice()            {QUIZ.setProperty(IDs::PlayerChoice, "", nullptr);}
