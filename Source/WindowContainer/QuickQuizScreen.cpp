/*
 ==============================================================================
 
 QuickQuizScreen.cpp
 Created: 20 May 2018 9:32:52pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "QuickQuizScreen.h"

void QuickQuizState::switchState (int i)
{
    owner->currentState = owner->stateList[i];
    owner->currentState->updateUI();
}

//==============================================================================

QuickQuizScreen::QuickQuizScreen (ValueTree& tree)
:   nextButton("Next"), vt(tree)
{
    addAndMakeVisible(&nextButton);
    nextButton.setLookAndFeel(&nblaf);
    nextButton.onClick = [this] { nextButtonClicked(); };
    
    addAndMakeVisible(&infoLabel);
    infoLabel.setJustificationType(Justification::centred);
    
    choiceButtons.add(new TextButton("Choice 1"));
    choiceButtons.add(new TextButton("Choice 2"));
    choiceButtons.add(new TextButton("Choice 3"));
    for (int i = 0; i < choiceButtons.size(); i++) {
        addAndMakeVisible(choiceButtons[i]);
        choiceButtons[i]->setClickingTogglesState(true);
        choiceButtons[i]->setRadioGroupId(8426);
        choiceButtons[i]->setLookAndFeel(&sblaf);
        choiceButtons[i]->onClick = [this, i] { setPlayerChoice(i); };
    }
    
    playButtons.add(new PlayStopButton("Choice 1"));
    playButtons.add(new PlayStopButton("Choice 2"));
    playButtons.add(new PlayStopButton("Choice 3"));
    for (int i = 0; i < playButtons.size(); i++) {
        addAndMakeVisible(playButtons[i]);
    }
    
    if (!vt.getChildWithName(IDs::QuickQuiz).isValid()) {
        ValueTree qq(IDs::QuickQuiz);
        vt.addChild(qq, -1, nullptr);
    }
    
    if (stateList.isEmpty())
    {
        stateList.addIfNotAlreadyThere(new BeginState(this, vt));
        stateList.addIfNotAlreadyThere(new ChooseState(this, vt));
        stateList.addIfNotAlreadyThere(new WinState(this, vt));
        stateList.addIfNotAlreadyThere(new LooseState(this, vt));
        stateList.addIfNotAlreadyThere(new EndState(this, vt));
    }
    currentState = stateList[0];
    currentState->updateUI();
}

QuickQuizScreen::~QuickQuizScreen()
{
    for (auto button : choiceButtons)
        button->setLookAndFeel(nullptr);
    nextButton.setLookAndFeel(nullptr);
    QUICKQUIZ.removeAllProperties(nullptr);
    stateList.clear(true);
    currentState = nullptr;
}

void QuickQuizScreen::resized()
{
    auto r (getLocalBounds().withTrimmedBottom(UI::footerHeight * 1.5));
    auto middle = r.withSizeKeepingCentre(r.getWidth(), UI::choiceButtonHeight + UI::footerHeight);
    auto playButtonArea = middle.removeFromBottom(UI::footerHeight);
    
    infoLabel.setBounds(r.removeFromTop(middle.getY()));
    
    choiceButtons[0]->setBounds(middle.withSizeKeepingCentre(UI::choiceButtonWidth, UI::choiceButtonHeight).translated(- (UI::choiceButtonWidth + 8), 0));
    choiceButtons[1]->setBounds(middle.withSizeKeepingCentre(UI::choiceButtonWidth, UI::choiceButtonHeight));
    choiceButtons[2]->setBounds(middle.withSizeKeepingCentre(UI::choiceButtonWidth, UI::choiceButtonHeight).translated(+ UI::choiceButtonWidth + 8, 0));
    
    playButtons[0]->setBounds(playButtonArea.withSizeKeepingCentre(UI::choiceButtonWidth, UI::footerHeight).translated(-(UI::choiceButtonWidth + 8), 0));
    playButtons[1]->setBounds(playButtonArea.withSizeKeepingCentre(UI::choiceButtonWidth, UI::footerHeight));
    playButtons[2]->setBounds(playButtonArea.withSizeKeepingCentre(UI::choiceButtonWidth, UI::footerHeight).translated(+ UI::choiceButtonWidth + 8, 0));
    
    nextButton.setBounds(r.removeFromRight(UI::choiceButtonWidth).removeFromBottom(UI::choiceButtonHeight).reduced(8));
}
