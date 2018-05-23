/*
 ==============================================================================
 
 QuickQuizScreen.h
 Created: 20 May 2018 9:32:52pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

/*
 <QUICKQUIZ
    Identifier QuizState      = "Quiz_State"
    Identifier Answer         = "Right_Answer",     int ButtonNumber
 >
    <PLAYER
        Identifier Choice     = "Choice",           int ButtonNumber
    />
 </QUICKQUIZ>
 
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Definitions.h"
#include "../Gui/PlayStopButton.h"

enum State {BEGIN   = 0,
            CHOOSE  = 1,
            WIN     = 2,
            LOOSE   = 3,
            END     = 4
};

class QuickQuizScreen;

//==============================================================================

class QuickQuizState {                                              // interface
public:
    QuickQuizState (QuickQuizScreen* qqs, ValueTree& tree)
    : vt(tree), owner(qqs)      {};
    virtual ~QuickQuizState()   {owner = nullptr;};
    
    virtual void nextButtonClicked  () = 0;
    virtual void updateUI           () = 0;
    virtual void setPlayerChoice    (int) = 0;
    
protected:
    ValueTree vt;
    QuickQuizScreen* owner;
    
    void switchState (int);
};
    
//==============================================================================

class QuickQuizScreen  : public Component {                         // context
    friend class QuickQuizState;
public:
    QuickQuizScreen (ValueTree&);
    ~QuickQuizScreen();
    
    void paint (Graphics&);
    void resized();

    // redirected to QuizStates
    void setPlayerChoice(int);
    void nextButtonClicked();
    
    Label                       infoLabel;
    TextButton                  nextButton;
    OwnedArray<TextButton>      choiceButtons;
    OwnedArray<PlayStopButton>  playButtons;
    
private:
    ValueTree vt;
    OwnedArray<QuickQuizState>       stateList;
    QuickQuizState*                  currentState;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuickQuizScreen)
};

//==============================================================================

class BeginState  : public QuickQuizState {                         // concrete State
public:
    BeginState (QuickQuizScreen* qqs, ValueTree& tree) : QuickQuizState(qqs, tree) {};
    ~BeginState()   {};
    
    void nextButtonClicked() override
    {
        switchState(State::CHOOSE);
    };
    
    void updateUI() override
    {
        owner->infoLabel.setText("click the button to begin a quiz", dontSendNotification);
        owner->nextButton.setButtonText("start");
        
        owner->choiceButtons[0]->setVisible(false);
        owner->choiceButtons[1]->setVisible(false);
        owner->choiceButtons[2]->setVisible(false);
        owner->playButtons[0]->setVisible(false);
        owner->playButtons[1]->setVisible(false);
        owner->playButtons[2]->setVisible(false);
    };
    
    void setPlayerChoice (int buttonNumber) override {};
};

class ChooseState  : public QuickQuizState {                        // concrete State
    public :
    ChooseState (QuickQuizScreen* qqs, ValueTree& tree) : QuickQuizState(qqs, tree)   {};
    ~ChooseState() {};
    
    void nextButtonClicked() override
    {
        // if player choice == right answer
        if (QUICKQUIZ.getChildWithName(IDs::Player).getProperty(IDs::Choice) == QUICKQUIZ.getProperty(IDs::Answer)) {
            switchState(State::WIN);
        }
        else switchState(State::LOOSE);
    };
    
    void updateUI() override
    {
        owner->infoLabel.setText("Choose State", dontSendNotification);
        
        owner->choiceButtons[0]->setVisible(true);
        owner->choiceButtons[1]->setVisible(true);
        owner->choiceButtons[2]->setVisible(true);
        owner->playButtons[0]->setVisible(false);
        owner->playButtons[1]->setVisible(false);
        owner->playButtons[2]->setVisible(false);
    };
    
    void setPlayerChoice (int buttonNumber) override
    {
        if (QUICKQUIZ.isValid()) {
            QUICKQUIZ.getOrCreateChildWithName(IDs::Player, nullptr).setProperty(IDs::Choice, buttonNumber, nullptr);
            owner->nextButton.setEnabled(true);
        }
        else if (vt.isValid()) DBG("ChooseState vt valid.");
        else DBG("ERROR! ValueTree in ChooseState not Valid!");
    };
};

class WinState  : public QuickQuizState {                           // concrete State
public:
    WinState (QuickQuizScreen* qqs, ValueTree& tree) : QuickQuizState(qqs, tree)   {};
    ~WinState() {};
    
    void nextButtonClicked() override
    {
        switchState(State::END);
    };
    
    void updateUI() override
    {
        owner->infoLabel.setText("Win State", dontSendNotification);
        owner->choiceButtons[0]->setVisible(false);
        owner->choiceButtons[1]->setVisible(false);
        owner->choiceButtons[2]->setVisible(false);
        
        //set the correct Answer to visible
        int rightAnswer = QUICKQUIZ.getProperty(IDs::Answer);
        owner->choiceButtons[rightAnswer]->setVisible(true);
        owner->choiceButtons[rightAnswer]->setEnabled(false);
    }
    
    void setPlayerChoice (int buttonNumber) override
    {
        
    };
};

class LooseState  : public QuickQuizState {                         // concrete State
public:
    LooseState (QuickQuizScreen* qqs, ValueTree& tree) : QuickQuizState(qqs, tree) {};
    ~LooseState()   {};
    
    void nextButtonClicked() override
    {
        switchState(State::END);
    };
    
    void updateUI() override
    {
        owner->infoLabel.setText("Loose State", dontSendNotification);
        owner->choiceButtons[0]->setVisible(false);
        owner->choiceButtons[1]->setVisible(false);
        owner->choiceButtons[2]->setVisible(false);
        
        //set the correct Answer to visible
        int rightAnswer = QUICKQUIZ.getProperty(IDs::Answer);
        owner->choiceButtons[rightAnswer]->setVisible(true);
        owner->choiceButtons[rightAnswer]->setEnabled(false);
        //set the correct PlayButton to visible
        owner->playButtons[rightAnswer]->setVisible(true);
    };
    
    void setPlayerChoice (int buttonNumber) override
    {
        
    };
};

class EndState  : public QuickQuizState {                           // concrete State
public:
    EndState (QuickQuizScreen* qqs, ValueTree& tree) : QuickQuizState(qqs, tree) {};
    ~EndState()   {};
    
    void nextButtonClicked() override
    {
        switchState(State::BEGIN);
    };
    
    void updateUI() override
    {
        owner->infoLabel.setText("End State", dontSendNotification);
        owner->nextButton.setButtonText("new quiz");
        
        owner->choiceButtons[0]->setVisible(false);
        owner->choiceButtons[1]->setVisible(false);
        owner->choiceButtons[2]->setVisible(false);
        owner->choiceButtons[0]->setEnabled(true);
        owner->choiceButtons[1]->setEnabled(true);
        owner->choiceButtons[2]->setEnabled(true);
        owner->playButtons[0]->setVisible(false);
        owner->playButtons[1]->setVisible(false);
        owner->playButtons[2]->setVisible(false);
    };
    
    void setPlayerChoice (int buttonNumber) override
    {
        
    };
};

