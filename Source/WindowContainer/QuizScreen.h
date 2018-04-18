/*
  ==============================================================================

    QuizScreen.h
    Created: 18 Mar 2018 9:32:52pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Gui/PlayStopButton.h"
#include "QuizStates/QuizState.h"
#include "QuizStates/ChooseState.h"
#include "QuizStates/WinState.h"
#include "QuizStates/LooseState.h"
#include "QuizStates/BeginState.h"

//==============================================================================
/*
*/
class QuizScreen :  public Component,
                    public Button::Listener,
                    public ValueTree::Listener
{
public:
    QuizScreen(ValueTree&);
    ~QuizScreen();

//==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
//==============================================================================
    void buttonClicked(Button*) override;
    
//==============================================================================
    void valueTreePropertyChanged (ValueTree&, const Identifier&) override;
    void valueTreeChildAdded (ValueTree&, ValueTree&) override;
    void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override;
    void valueTreeChildOrderChanged (ValueTree&, int, int) override;
    void valueTreeParentChanged (ValueTree&) override;
    void valueTreeRedirected (ValueTree&) override;

//==============================================================================
    void saveGameStats();
    void update (int);
    
    // redirected to QuizStates
    void setChoice(String);
    void next();
    
private:
    ValueTree quizNode;
    
    OwnedArray<QuizState>       stateList;
    QuizState*                  currentState;
    
    TextButton choice1Button, choice2Button, choice3Button, nextButton;
    PlayStopButton play1Button, play2Button, play3Button;
    Label roundCounter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuizScreen)
};
