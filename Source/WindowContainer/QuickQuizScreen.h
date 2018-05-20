/*
 ==============================================================================
 
 QuickQuizScreen.h
 Created: 20 May 2018 9:32:52pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

// All in one Screen for the 1,2,3 Quiz
// This will replace the old QuizScreen and its QuizStates.

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Definitions.h"
#include "../Gui/PlayStopButton.h"

class QuickQuizScreen;

//==============================================================================

class QuickQuizState {                                              // interface
public:
    QuickQuizState (ValueTree& tree) : vt(tree) {};
    virtual ~QuickQuizState() {};
    
    virtual void nextButtonClicked  () = 0;
    virtual void updateUI           () = 0;
    virtual void setPlayerChoice    (String) = 0;
    
protected:
    ValueTree vt;
    
    void switchState (QuickQuizScreen*, int);
};

//==============================================================================

class ChooseState  : public QuickQuizState {                        // concrete State
public :
    ChooseState (ValueTree& tree) : QuickQuizState(tree)   {};
    ~ChooseState() {};
    
    void nextButtonClicked  () override {};
    void updateUI           () override {};
    void setPlayerChoice    (String) override {};
};

//==============================================================================

class QuickQuizScreen  : public Component {
    friend class QuickQuizState;
public:
    QuickQuizScreen (ValueTree& tree)
    : vt(tree), choice1Button("Choice 1"), choice2Button("Choice 2"), choice3Button("Choice 3"),
    nextButton("Next"), play1Button("Play Choice 1"), play2Button("Play Choice 2"), play3Button("Play Choice 3")
    {
        addAndMakeVisible(&choice1Button);
        addAndMakeVisible(&choice2Button);
        addAndMakeVisible(&choice3Button);
        addAndMakeVisible(&play1Button);
        addAndMakeVisible(&play2Button);
        addAndMakeVisible(&play3Button);
        addAndMakeVisible(&nextButton);
        
        if (stateList.isEmpty())
        {
            stateList.addIfNotAlreadyThere(new ChooseState(vt));
        }
        currentState = stateList[0];
    };
    ~QuickQuizScreen()
    {
        QUIZ.removeAllProperties(nullptr);
        stateList.clear(true);
        currentState = nullptr;
    };
    
    void paint (Graphics&) {};
    void resized()
    {
        auto r (getLocalBounds());
        
        Grid grid;
        grid.templateRows       = { Grid::TrackInfo (1_fr), Grid::TrackInfo (1_fr) };
        grid.templateColumns    = { Grid::TrackInfo (1_fr), Grid::TrackInfo (1_fr), Grid::TrackInfo (1_fr) };
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
    };

    // redirected to QuizStates
    void setPlayerChoice(String s) { currentState->setPlayerChoice(s); };
    void nextButtonClicked()       { currentState->nextButtonClicked(); };
    
private:
    ValueTree vt;
    OwnedArray<QuickQuizState>       stateList;
    QuickQuizState*                  currentState;
    
    TextButton choice1Button, choice2Button, choice3Button, nextButton;
    PlayStopButton play1Button, play2Button, play3Button;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuickQuizScreen)
};


