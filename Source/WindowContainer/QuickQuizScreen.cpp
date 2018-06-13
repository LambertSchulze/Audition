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

void BeginState::newQuiz()
{
    game.newQuickQuiz();
    
    // select a new File for playback
    if ((bool) FILELIST[IDs::Repeat] == true) {
        //int selectedFile = FILELIST[IDs::SelectedFile];
        //if (selectedFile == FILELIST.getNumChildren() - 1)
        //    selectedFile = -1;
        //
        //FILELIST.setProperty(IDs::SelectedFile, selectedFile + 1, nullptr);
    }
    
    else if ((bool) FILELIST[IDs::Shuffle] == true) {
        Random r;
        //int selectedFile = FILELIST[IDs::SelectedFile];
        //int newSelection;
        //do {
        //    newSelection = r.nextInt(FILELIST.getNumChildren());
        //} while (newSelection == selectedFile);
        //
        //FILELIST.setProperty(IDs::SelectedFile, newSelection, nullptr);
    }
}

//==============================================================================

QuickQuizScreen::QuickQuizScreen (ValueTree& tree)
:   nextButton("Next"), vt(tree)
{
    addAndMakeVisible(&nextButton);
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
        choiceButtons[i]->setLookAndFeel(&laf);
    }    
    choiceButtons[0]->onClick = [this] { setPlayerChoice(0); };
    choiceButtons[1]->onClick = [this] { setPlayerChoice(1); };
    choiceButtons[2]->onClick = [this] { setPlayerChoice(2); };
        
    if (!vt.getChildWithName(IDs::QuickQuiz).isValid()) {
        ValueTree qq(IDs::QuickQuiz);
        vt.addChild(qq, -1, nullptr);
        //DBG("added QuickQuiz Node");
    }
    
    if (stateList.isEmpty())
    {
        stateList.addIfNotAlreadyThere(new BeginState(this, vt));
        stateList.addIfNotAlreadyThere(new ChooseState(this, vt));
        stateList.addIfNotAlreadyThere(new WinState(this, vt));
        stateList.addIfNotAlreadyThere(new LooseState(this, vt));
        stateList.addIfNotAlreadyThere(new EndState(this, vt));
    }
    currentState = stateList[1];
    currentState->updateUI();
}

QuickQuizScreen::~QuickQuizScreen()
{
    for (auto button : choiceButtons)
        button->setLookAndFeel(nullptr);
    QUICKQUIZ.removeAllProperties(nullptr);
    stateList.clear(true);
    currentState = nullptr;
}

void QuickQuizScreen::resized()
{
    auto r (getLocalBounds().withTrimmedBottom(UI::footerHeight * 1.5));
    auto middle = r.withSizeKeepingCentre(r.getWidth(), UI::choiceButtonHeight);
    
    infoLabel.setBounds(r.removeFromTop(middle.getY()));
    
    choiceButtons[0]->setBounds(middle.withSizeKeepingCentre(UI::choiceButtonWidth, UI::choiceButtonHeight).translated(- (UI::choiceButtonWidth + 8), 0));
    choiceButtons[1]->setBounds(middle.withSizeKeepingCentre(UI::choiceButtonWidth, UI::choiceButtonHeight));
    
    //choiceButtons[1]->setBounds(r.reduced(100));
    
    choiceButtons[2]->setBounds(middle.withSizeKeepingCentre(UI::choiceButtonWidth, UI::choiceButtonHeight).translated(+ UI::choiceButtonWidth + 8, 0));
    
    nextButton.setBounds(r.removeFromRight(120).removeFromBottom(120).reduced(8));
}
