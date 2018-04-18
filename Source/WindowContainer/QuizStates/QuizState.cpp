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
QuizState::QuizState (ValueTree& vt)
:   quizNode(vt)
{}

QuizState::~QuizState()
{}

String QuizState::updateCounter     ()          {return "";}
void QuizState::setChoice           (String)    {}
void QuizState::next                ()          {}

void QuizState::newQuiz             ()
{
    // get 3 random Effects of the List of all Effects
    
    ValueTree effectListNode    = quizNode.getParent().getChildWithName(IDs::EffectList);
    int numOfAllEffects     = effectListNode.getNumChildren();
    
    int randEffect1         = random.nextInt(numOfAllEffects);
    
    int randEffect2         = random.nextInt(numOfAllEffects);
    
    int randEffect3         = random.nextInt(numOfAllEffects);
 
    quizNode.getChild(0).setProperty(IDs::Name, effectListNode.getChild(randEffect1).getProperty(IDs::EffectName), nullptr);
    quizNode.getChild(1).setProperty(IDs::Name, effectListNode.getChild(randEffect2).getProperty(IDs::EffectName), nullptr);
    quizNode.getChild(2).setProperty(IDs::Name, effectListNode.getChild(randEffect3).getProperty(IDs::EffectName), nullptr);
    
    // set one of them as the right one
    
    if (quizNode.getChildWithProperty(IDs::isRight, true).isValid()) quizNode.getChildWithProperty(IDs::isRight, true).setProperty(IDs::isRight, false, nullptr);
    if (effectListNode.getChildWithProperty(IDs::forPlayback, true).isValid()) effectListNode.getChildWithProperty(IDs::forPlayback, true).setProperty(IDs::forPlayback, false, nullptr);
    
    int rightAnswer = random.nextInt(3);
    
    quizNode.getChild(rightAnswer).setProperty(IDs::isRight, true, nullptr);
    
    effectListNode.getChildWithProperty(IDs::EffectName, quizNode.getChildWithProperty(IDs::isRight, true).getProperty(IDs::Name)).setProperty(IDs::forPlayback, true, nullptr);


//    std::cout << "right Answer: " << quizNode.getChild(rightAnswer).getProperty(IDs::Name).toString() << "\n";
}

void QuizState::deletePlayerChoice()            {quizNode.setProperty(IDs::PlayerChoice, "", nullptr);}
