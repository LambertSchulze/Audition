/*
  ==============================================================================

    QuizScreen.cpp
    Created: 18 Mar 2018 9:32:52pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "QuizScreen.h"
#include "../Definitions/Definitions.h"

//==============================================================================
QuizScreen::QuizScreen(ValueTree& vt)
:   quizNode(vt),
    choice1Button("Choice 1 Button"),
    choice2Button("Choice 2 Button"),
    choice3Button("Choice 3 Button"),
    nextButton("Next Button"),
    play1Button("Play Choice 1 Button"),
    play2Button("Play Choice 2 Button"),
    play3Button("Play Choice 3 Button")
{
    quizNode = quizNode.getChildWithName(IDs::Quiz);
    
    addAndMakeVisible(&choice1Button);
    addAndMakeVisible(&choice2Button);
    addAndMakeVisible(&choice3Button);
    addAndMakeVisible(&play1Button);
    addAndMakeVisible(&play2Button);
    addAndMakeVisible(&play3Button);
    addAndMakeVisible(&roundCounter);
    addAndMakeVisible(&nextButton);
    
    roundCounter    .setJustificationType(Justification::centred);
    choice1Button   .addListener(this);
    choice2Button   .addListener(this);
    choice3Button   .addListener(this);
    nextButton      .addListener(this);
    
    quizNode.addListener(this);
    
    if (stateList.isEmpty())
    {
        stateList.addIfNotAlreadyThere(new ChooseState(quizNode));
        stateList.addIfNotAlreadyThere(new WinState(quizNode));
        stateList.addIfNotAlreadyThere(new LooseState(quizNode));
        stateList.addIfNotAlreadyThere(new BeginState(quizNode));
    }
    currentState = stateList[3];
    update(3);
}

QuizScreen::~QuizScreen()
{
    choice1Button   .removeListener(this);
    choice2Button   .removeListener(this);
    choice3Button   .removeListener(this);
    nextButton      .removeListener(this);
    
    quizNode.removeAllProperties(nullptr);
    
    stateList.clear(true);
    currentState = nullptr;
}

void QuizScreen::paint (Graphics& g) {}

void QuizScreen::resized()
{
    auto r (getLocalBounds());
    auto rBR (r.getBottomRight());
    choice1Button.setBounds(0, 0, 100, 100);
    choice2Button.setBounds(0, 0, 100, 100);
    choice3Button.setBounds(0, 0, 100, 100);
    choice1Button.setCentreRelative(0.3, 0.5);
    choice2Button.setCentreRelative(0.5, 0.5);
    choice3Button.setCentreRelative(0.7, 0.5);
    
    play1Button.setBounds(0, 0, 100, 100);
    play2Button.setBounds(0, 0, 100, 100);
    play3Button.setBounds(0, 0, 100, 100);
    play1Button.setCentreRelative(0.3, 0.7);
    play2Button.setCentreRelative(0.5, 0.7);
    play3Button.setCentreRelative(0.7, 0.7);
    roundCounter.setBounds(0, 0, r.getWidth(), 100);
    nextButton.setBounds(rBR.x - 100, rBR.y -100, 100, 100);
}

void QuizScreen::buttonClicked(Button* b)
{
    if (b == &choice1Button) currentState->setChoice(quizNode.getChild(0).getProperty(IDs::Name));
    if (b == &choice2Button) currentState->setChoice(quizNode.getChild(1).getProperty(IDs::Name));
    if (b == &choice3Button) currentState->setChoice(quizNode.getChild(2).getProperty(IDs::Name));
    if (b == &nextButton)
    {
        currentState->next();
        update((int) quizNode.getProperty(IDs::QuizState));
    }
}

void QuizScreen::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{    
    if (property == IDs::QuizState) currentState = stateList[quizNode.getProperty(IDs::QuizState)];
}

void QuizScreen::valueTreeChildAdded (ValueTree&, ValueTree&) {}
void QuizScreen::valueTreeChildRemoved (ValueTree&, ValueTree&, int) {}
void QuizScreen::valueTreeChildOrderChanged (ValueTree&, int, int) {}
void QuizScreen::valueTreeParentChanged (ValueTree&) {}
void QuizScreen::valueTreeRedirected (ValueTree&) {}

//==============================================================================
void QuizScreen::update (int state)
{
    switch (state)
    {
        case 0: // Choose State
            // hide play buttons and set next to solve
            // show choice buttons if hidden
            
            roundCounter.setText(currentState->updateCounter(), dontSendNotification);
            
            play1Button.setVisible(false);
            play2Button.setVisible(false);
            play3Button.setVisible(false);
            nextButton.setButtonText("Solve");
            choice1Button.setVisible(true);
            choice2Button.setVisible(true);
            choice3Button.setVisible(true);
            choice1Button.setEnabled(true);
            choice2Button.setEnabled(true);
            choice3Button.setEnabled(true);
            
            choice1Button.setButtonText(quizNode.getChild(0).getProperty(IDs::Name).toString());
            choice2Button.setButtonText(quizNode.getChild(1).getProperty(IDs::Name).toString());
            choice3Button.setButtonText(quizNode.getChild(2).getProperty(IDs::Name).toString());
            
            break;
            
        case 1: // Won State
            // hide buttons with wrong answers
            // make right button unclickable
            // set next button to next
            
            roundCounter.setText(currentState->updateCounter(), dontSendNotification);
            
            choice1Button.setVisible(quizNode.getChild(0).getProperty(IDs::isRight));
            choice2Button.setVisible(quizNode.getChild(1).getProperty(IDs::isRight));
            choice3Button.setVisible(quizNode.getChild(2).getProperty(IDs::isRight));
            choice1Button.setEnabled(false);
            choice2Button.setEnabled(false);
            choice3Button.setEnabled(false);
            
            nextButton.setButtonText("Next");
            break;
            
        case 2: // Loose State
            // hide button with wrong answer
            // show the play button of the player choice
            // make right button unclickable
            // set next button to next
            
            roundCounter.setText(currentState->updateCounter(), dontSendNotification);
            
            play1Button.setVisible(quizNode.getChild(0).getProperty(IDs::isRight));
            play2Button.setVisible(quizNode.getChild(1).getProperty(IDs::isRight));
            play3Button.setVisible(quizNode.getChild(2).getProperty(IDs::isRight));
            choice1Button.setVisible(quizNode.getChild(0).getProperty(IDs::isRight));
            choice2Button.setVisible(quizNode.getChild(1).getProperty(IDs::isRight));
            choice3Button.setVisible(quizNode.getChild(2).getProperty(IDs::isRight));
            choice1Button.setEnabled(!(quizNode.getChild(0).getProperty(IDs::isRight)));
            choice2Button.setEnabled(!(quizNode.getChild(1).getProperty(IDs::isRight)));
            choice3Button.setEnabled(!(quizNode.getChild(2).getProperty(IDs::isRight)));
                        
            nextButton.setButtonText("Next");
            break;
            
        case 3: // Begin State
            
            roundCounter.setText(currentState->updateCounter(), dontSendNotification);
            
            play1Button.setVisible(true);
            play2Button.setVisible(true);
            play3Button.setVisible(true);
            choice1Button.setVisible(true);
            choice2Button.setVisible(true);
            choice3Button.setVisible(true);
            nextButton.setButtonText("Begin Quiz");
            break;
    }
}

void QuizScreen::setChoice(String choice)   {currentState->setChoice(choice);}
void QuizScreen::next()                     {currentState->next();}

