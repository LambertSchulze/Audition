/*
 ==============================================================================
 
 QuickQuizScreen.h
 Created: 20 May 2018 9:32:52pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

/*
 <QUICKQUIZ
    Identifier RightEffect    = "Right_Effect";     int EffectNumber
    Identifier WrongEffectA   = "Wrong_Effect_A";   int EffectNumber
    Identifier WrongEffectB   = "Wrong_Effect_B";   int EffectNumber
    Identifier RightButton    = "Right_Button_Num"; int ButtonNumber
    Identifier WrongButtonA   = "Wrong_Button_A";   int ButtonNumber
    Identifier WrongButtonB   = "Wrong_Button_B";   int ButtonNumber
 >
    <PLAYER
 Identifier Choice     = "Choice";                  int ButtonNumber
    />
 </QUICKQUIZ>
 
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Definitions.h"
#include "../Core/RandomEffects.h"

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
    
    virtual void nextButtonClicked      () = 0;
    virtual void updateUI               () = 0;
    virtual void setPlayerChoice        (int) = 0;
    
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
    
    void paint (Graphics&)          {};
    void resized();

    // redirected to QuizStates
    void setPlayerChoice(int num)   {currentState->setPlayerChoice(num);};
    void nextButtonClicked()        {currentState->nextButtonClicked();};
    
    Label                       infoLabel;
    TextButton                  nextButton;
    OwnedArray<TextButton>      choiceButtons;
    
private:
    ValueTree vt;
    OwnedArray<QuickQuizState>       stateList;
    QuickQuizState*                  currentState;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuickQuizScreen)
};

//==============================================================================

class BeginState  : public QuickQuizState {                         // concrete State
public:
    BeginState (QuickQuizScreen* qqs, ValueTree& tree) : QuickQuizState(qqs, tree), game(tree) {};
    ~BeginState()   {};
    
    void nextButtonClicked() override
    {
        newQuiz();
        //TRANSPORT.setProperty(IDs::EffectToPlay, QUICKQUIZ[IDs::RightEffect], nullptr);
        switchState(State::CHOOSE);
    };
    
    void updateUI() override
    {
        owner->infoLabel.setText("click the button to begin a quiz", dontSendNotification);
        owner->nextButton.setButtonText("start");
        
        owner->choiceButtons[0]->setVisible(false);
        owner->choiceButtons[1]->setVisible(false);
        owner->choiceButtons[2]->setVisible(false);
    };
    
    void setPlayerChoice (int buttonNumber) override {};
    
    void newQuiz();
    RandomEffects game;
};

class ChooseState  : public QuickQuizState {                        // concrete State
    public :
    ChooseState (QuickQuizScreen* qqs, ValueTree& tree) : QuickQuizState(qqs, tree)   {};
    ~ChooseState() {};
    
    void nextButtonClicked() override
    {
        // if player choice == right answer
        if (QUICKQUIZ.getChildWithName(IDs::Player).getProperty(IDs::Choice) == QUICKQUIZ.getProperty(IDs::RightButton)) {
            switchState(State::WIN);
        }
        else switchState(State::LOOSE);
    };
    
    void updateUI() override
    {
        owner->infoLabel.setText("Choose State", dontSendNotification);
        owner->nextButton.setButtonText("solve");
        owner->nextButton.setEnabled(false);
        
        // write the Effect names on the buttons
        owner->choiceButtons[QUICKQUIZ[IDs::RightButton]]->setButtonText(EFFECTLIST.getChild(QUICKQUIZ[IDs::RightEffect])[IDs::EffectName].toString());
        owner->choiceButtons[QUICKQUIZ[IDs::WrongButtonA]]->setButtonText(EFFECTLIST.getChild(QUICKQUIZ[IDs::WrongEffectA])[IDs::EffectName].toString());
        owner->choiceButtons[QUICKQUIZ[IDs::WrongButtonB]]->setButtonText(EFFECTLIST.getChild(QUICKQUIZ[IDs::WrongEffectB])[IDs::EffectName].toString());
        
        owner->choiceButtons[0]->setVisible(true);
        owner->choiceButtons[1]->setVisible(true);
        owner->choiceButtons[2]->setVisible(true);
    };
    
    void setPlayerChoice (int buttonNumber) override
    {
        QUICKQUIZ.getChildWithName(IDs::Player).setProperty(IDs::Choice, buttonNumber, nullptr);
        owner->nextButton.setEnabled(true);
        
        //DBG("Player Choice: " << QUICKQUIZ.getChildWithName(IDs::Player)[IDs::Choice].toString());
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
        owner->infoLabel.setText("Win State: The correct Effect is shown.", dontSendNotification);
        owner->nextButton.setButtonText("next");
        
        owner->choiceButtons[0]->setToggleState(false, dontSendNotification);
        owner->choiceButtons[1]->setToggleState(false, dontSendNotification);
        owner->choiceButtons[2]->setToggleState(false, dontSendNotification);
        owner->choiceButtons[0]->setVisible(false);
        owner->choiceButtons[1]->setVisible(false);
        owner->choiceButtons[2]->setVisible(false);
        
        //set the correct Answer to visible
        int rightButtonNum = QUICKQUIZ.getProperty(IDs::RightButton);
        owner->choiceButtons[rightButtonNum]->setVisible(true);
        owner->choiceButtons[rightButtonNum]->setEnabled(false);
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
        owner->infoLabel.setText("Loose State: This was the correct one and you chose this.", dontSendNotification);
        owner->nextButton.setButtonText("next");
        
        owner->choiceButtons[0]->setToggleState(false, dontSendNotification);
        owner->choiceButtons[1]->setToggleState(false, dontSendNotification);
        owner->choiceButtons[2]->setToggleState(false, dontSendNotification);
        owner->choiceButtons[0]->setVisible(false);
        owner->choiceButtons[1]->setVisible(false);
        owner->choiceButtons[2]->setVisible(false);
        
        //make the correct Answer Button visible
        int rightButtonNum = QUICKQUIZ.getProperty(IDs::RightButton);
        owner->choiceButtons[rightButtonNum]->setVisible(true);
        owner->choiceButtons[rightButtonNum]->setEnabled(false);
        
        //make the Choice and PlayButton of the players choice visible
        int choiceButtonNum = QUICKQUIZ.getChildWithName(IDs::Player)[IDs::Choice];
        owner->choiceButtons[choiceButtonNum]->setVisible(true);
        owner->choiceButtons[choiceButtonNum]->setEnabled(false);
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
//        TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
//        TRANSPORT.removeProperty(IDs::EffectToPlay, nullptr);
        
        owner->infoLabel.setText("End State", dontSendNotification);
        owner->nextButton.setButtonText("new quiz");
        
        owner->choiceButtons[0]->setVisible(false);
        owner->choiceButtons[1]->setVisible(false);
        owner->choiceButtons[2]->setVisible(false);
        owner->choiceButtons[0]->setEnabled(true);
        owner->choiceButtons[1]->setEnabled(true);
        owner->choiceButtons[2]->setEnabled(true);
    };
    
    void setPlayerChoice (int buttonNumber) override
    {
        
    };
};
