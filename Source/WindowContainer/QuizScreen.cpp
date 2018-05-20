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
QuizScreen::QuizScreen(ValueTree& tree)
:   vt(tree),
    choice1Button("Choice 1 Button"),
    choice2Button("Choice 2 Button"),
    choice3Button("Choice 3 Button"),
    nextButton("Next Button"),
    play1Button("Play Choice 1 Button"),
    play2Button("Play Choice 2 Button"),
    play3Button("Play Choice 3 Button")
{
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
    
    vt.addListener(this);
    
    if (stateList.isEmpty())
    {
        stateList.addIfNotAlreadyThere(new ChooseState(vt));
        stateList.addIfNotAlreadyThere(new WinState(vt));
        stateList.addIfNotAlreadyThere(new LooseState(vt));
        stateList.addIfNotAlreadyThere(new BeginState(vt));
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
    vt              .removeListener(this);
    
    QUIZ.removeAllProperties(nullptr);
    
    stateList.clear(true);
    currentState = nullptr;
}

void QuizScreen::paint (Graphics& g) {}

void QuizScreen::resized()
{
    auto r (getLocalBounds());

    roundCounter.setBounds(r.removeFromTop(r.getHeight() / 3));

    Grid grid;
    grid.templateRows       = { Grid::TrackInfo (1_fr), Grid::TrackInfo (1_fr) };
    grid.templateColumns    = { Grid::TrackInfo (1_fr), Grid::TrackInfo (1_fr), Grid::TrackInfo (1_fr) };
    //grid.setGap(Grid::Px (10));
    grid.items =
    {
        GridItem(choice1Button).withWidth(180).withHeight(80).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center),
        GridItem(choice2Button).withWidth(180).withHeight(80).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center),
        GridItem(choice3Button).withWidth(180).withHeight(80).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center),
        GridItem(play1Button).withWidth(50).withHeight(50).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center),
        GridItem(play2Button).withWidth(50).withHeight(50).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center),
        GridItem(play3Button).withWidth(50).withHeight(50).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center)
    };
    grid.performLayout(r.removeFromTop(r.getHeight() / 2));
    
    nextButton.setBounds(r.removeFromRight(120).removeFromBottom(120));
}

void QuizScreen::buttonClicked(Button* b)
{
    if (b == &choice1Button) currentState->setChoice(QUIZ.getChild(0).getProperty(IDs::Name));
    if (b == &choice2Button) currentState->setChoice(QUIZ.getChild(1).getProperty(IDs::Name));
    if (b == &choice3Button) currentState->setChoice(QUIZ.getChild(2).getProperty(IDs::Name));
    if (b == &nextButton)
    {
        currentState->next();
        update((int) QUIZ.getProperty(IDs::QuizState));
    }
}

void QuizScreen::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{    
    if (property == IDs::QuizState) currentState = stateList[QUIZ.getProperty(IDs::QuizState)];
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
            
            choice1Button.setButtonText(QUIZ.getChild(0).getProperty(IDs::Name).toString());
            choice2Button.setButtonText(QUIZ.getChild(1).getProperty(IDs::Name).toString());
            choice3Button.setButtonText(QUIZ.getChild(2).getProperty(IDs::Name).toString());
            
            break;
            
        case 1: // Won State
            // hide buttons with wrong answers
            // make right button unclickable
            // set next button to next
            
            roundCounter.setText(currentState->updateCounter(), dontSendNotification);
            
            choice1Button.setVisible(QUIZ.getChild(0).getProperty(IDs::isRight));
            choice2Button.setVisible(QUIZ.getChild(1).getProperty(IDs::isRight));
            choice3Button.setVisible(QUIZ.getChild(2).getProperty(IDs::isRight));
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
            
            play1Button.setVisible(QUIZ.getChild(0).getProperty(IDs::isRight));
            play2Button.setVisible(QUIZ.getChild(1).getProperty(IDs::isRight));
            play3Button.setVisible(QUIZ.getChild(2).getProperty(IDs::isRight));
            choice1Button.setVisible(QUIZ.getChild(0).getProperty(IDs::isRight));
            choice2Button.setVisible(QUIZ.getChild(1).getProperty(IDs::isRight));
            choice3Button.setVisible(QUIZ.getChild(2).getProperty(IDs::isRight));
            choice1Button.setEnabled(!(QUIZ.getChild(0).getProperty(IDs::isRight)));
            choice2Button.setEnabled(!(QUIZ.getChild(1).getProperty(IDs::isRight)));
            choice3Button.setEnabled(!(QUIZ.getChild(2).getProperty(IDs::isRight)));
                        
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

