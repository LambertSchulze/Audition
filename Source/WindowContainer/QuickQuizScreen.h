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
#include "../Core/TransportManager.h"
#include "../Gui/PlayStopButton.h"
#include "SelectButtonLookAndFeel.h"
#include "NextButtonLookAndFeel.h"

enum State {BEGIN   = 0,
            CHOOSE  = 1,
            WIN     = 2,
            LOOSE   = 3,
            END     = 4};

class QuickQuizScreen;

//==============================================================================

class QuickQuizState
{
public:
    QuickQuizState (QuickQuizScreen* qqs, ValueTree& tree)
        : vt(tree), owner(qqs)
    {};
    
    virtual ~QuickQuizState()   {owner = nullptr;};
    
    virtual void nextButtonClicked() = 0;
    virtual void updateUI() = 0;
    virtual void setPlayerChoice(int) = 0;
    
protected:
    ValueTree vt;
    QuickQuizScreen* owner;
    
    void switchState(int);
};
    
//==============================================================================

class QuickQuizScreen : public Component
{
    friend class QuickQuizState;
    
public:
    QuickQuizScreen (ValueTree&);
    ~QuickQuizScreen();
    
    void resized();

    // redirected to QuizStates
    void setPlayerChoice(int num)   {currentState->setPlayerChoice(num);};
    void nextButtonClicked()        {currentState->nextButtonClicked();};
    
    Label infoLabel;
    TextButton nextButton;
    OwnedArray<TextButton> choiceButtons;
    
private:
    ValueTree vt;
    
    OwnedArray<PlayStopButton> playButtons;
    
    OwnedArray<QuickQuizState> stateList;
    QuickQuizState* currentState;
    SelectButtonLookAndFeel sblaf;
    NextButtonLookAndFeel nblaf;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuickQuizScreen)
};

//==============================================================================

class BeginState : public QuickQuizState
{
public:
    BeginState (QuickQuizScreen* qqs, ValueTree& tree)
        : QuickQuizState(qqs, tree), game(tree)
    {};
    
    ~BeginState() {};
    
    void nextButtonClicked() override
    {
        game.newQuickQuiz();
        
        TransportManager::instance->setEffect((int) QUICKQUIZ[IDs::RightEffect]);
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
    
private:
    RandomEffects game;
};

class ChooseState : public QuickQuizState
{
    public :
    ChooseState (QuickQuizScreen* qqs, ValueTree& tree)
        : QuickQuizState(qqs, tree)
    {};
    
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
        owner->infoLabel.setText("What effect is applied?", dontSendNotification);
        owner->nextButton.setButtonText("solve");
        owner->nextButton.setEnabled(false);
        
        // write the Effect names on the buttons
        owner->choiceButtons[QUICKQUIZ[IDs::RightButton]]->setButtonText(TransportManager::instance->effectList[QUICKQUIZ[IDs::RightEffect]]->getDetailedName());
        owner->choiceButtons[QUICKQUIZ[IDs::WrongButtonA]]->setButtonText(TransportManager::instance->effectList[QUICKQUIZ[IDs::WrongEffectA]]->getDetailedName());
        owner->choiceButtons[QUICKQUIZ[IDs::WrongButtonB]]->setButtonText(TransportManager::instance->effectList[QUICKQUIZ[IDs::WrongEffectB]]->getDetailedName());
        
        owner->choiceButtons[0]->setVisible(true);
        owner->choiceButtons[1]->setVisible(true);
        owner->choiceButtons[2]->setVisible(true);
        owner->choiceButtons[0]->setEnabled(true);
        owner->choiceButtons[1]->setEnabled(true);
        owner->choiceButtons[2]->setEnabled(true);
        owner->choiceButtons[0]->setColour(TextButton::buttonColourId, AuditionColours::white);
        owner->choiceButtons[1]->setColour(TextButton::buttonColourId, AuditionColours::white);
        owner->choiceButtons[2]->setColour(TextButton::buttonColourId, AuditionColours::white);
    };
    
    void setPlayerChoice (int buttonNumber) override
    {
        QUICKQUIZ.getChildWithName(IDs::Player).setProperty(IDs::Choice, buttonNumber, nullptr);
        owner->nextButton.setEnabled(true);
    };
};

class WinState : public QuickQuizState
{
public:
    WinState (QuickQuizScreen* qqs, ValueTree& tree)
        : QuickQuizState(qqs, tree), game(tree)
    {};
    
    ~WinState() {};
    
    void nextButtonClicked() override
    {
        game.newQuickQuiz();
        
        TransportManager::instance->setEffect((int) QUICKQUIZ[IDs::RightEffect]);
        switchState(State::CHOOSE);
    };
    
    void updateUI() override
    {
        owner->infoLabel.setText("You are right!", dontSendNotification);
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
        owner->choiceButtons[rightButtonNum]->setColour(TextButton::buttonColourId, AuditionColours::green);
    }
    
    void setPlayerChoice (int buttonNumber) override {};
    
private:
    RandomEffects game;
};

class LooseState : public QuickQuizState
{
public:
    LooseState (QuickQuizScreen* qqs, ValueTree& tree)
        : QuickQuizState(qqs, tree), game(tree)
    {};
    
    ~LooseState() {};
    
    void nextButtonClicked() override
    {
        game.newQuickQuiz();
        
        TransportManager::instance->setEffect((int) QUICKQUIZ[IDs::RightEffect]);
        switchState(State::CHOOSE);
    };
    
    void updateUI() override
    {
        owner->infoLabel.setText("That was wrong. This was the correct one:", dontSendNotification);
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
        owner->choiceButtons[rightButtonNum]->setColour(TextButton::buttonColourId, AuditionColours::green);
        
        //make the Choice and PlayButton of the players choice visible
        int choiceButtonNum = QUICKQUIZ.getChildWithName(IDs::Player)[IDs::Choice];
        owner->choiceButtons[choiceButtonNum]->setVisible(true);
        owner->choiceButtons[choiceButtonNum]->setEnabled(false);
        owner->choiceButtons[choiceButtonNum]->setColour(TextButton::buttonColourId, AuditionColours::blue);
        
        //owner->
    };
    
    void setPlayerChoice (int buttonNumber) override {};
    
private:
    RandomEffects game;
};

class EndState : public QuickQuizState
{
public:
    EndState (QuickQuizScreen* qqs, ValueTree& tree)
        : QuickQuizState(qqs, tree)
    {};
    
    ~EndState() {};
    
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
    };
    
    void setPlayerChoice (int buttonNumber) override {};
};
