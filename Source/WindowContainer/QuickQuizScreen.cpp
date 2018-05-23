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
}

//==============================================================================

QuickQuizScreen::QuickQuizScreen (ValueTree& tree)
:   nextButton("Next"), vt(tree)
{
    playButtons.add(new PlayStopButton("Play Choice 1", vt));
    playButtons.add(new PlayStopButton("Play Choice 2", vt));
    playButtons.add(new PlayStopButton("Play Choice 3", vt));
    addAndMakeVisible(playButtons[0]);
    addAndMakeVisible(playButtons[1]);
    addAndMakeVisible(playButtons[2]);
    addAndMakeVisible(&nextButton);
    addAndMakeVisible(&infoLabel);
    nextButton.onClick      = [this] { nextButtonClicked(); };
 
    choiceButtons.add(new TextButton("Choice 1"));
    choiceButtons.add(new TextButton("Choice 2"));
    choiceButtons.add(new TextButton("Choice 3"));
    for (int i = 0; i < choiceButtons.size(); i++) {
        addAndMakeVisible(choiceButtons[i]);
        choiceButtons[i]->setClickingTogglesState(true);
        choiceButtons[i]->setRadioGroupId(8426);
    }
    choiceButtons[0]->onClick   = [this] { setPlayerChoice(0); };
    choiceButtons[1]->onClick   = [this] { setPlayerChoice(1); };
    choiceButtons[2]->onClick   = [this] { setPlayerChoice(2); };
    
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
    currentState = stateList[0];
    currentState->updateUI();
}

QuickQuizScreen::~QuickQuizScreen()
{
    QUICKQUIZ.removeAllProperties(nullptr);
    stateList.clear(true);
    currentState = nullptr;
}

void QuickQuizScreen::resized()
{
    auto r (getLocalBounds());
    
    infoLabel.setBounds(r.removeFromTop(30));
    
    Grid grid;
    grid.templateRows       = { Grid::TrackInfo (1_fr), Grid::TrackInfo (1_fr) };
    grid.templateColumns    = { Grid::TrackInfo (1_fr), Grid::TrackInfo (1_fr), Grid::TrackInfo (1_fr) };
    grid.items =
    {
        GridItem(choiceButtons[0]).withWidth(180).withHeight(80).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center),
        GridItem(choiceButtons[1]).withWidth(180).withHeight(80).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center),
        GridItem(choiceButtons[2]).withWidth(180).withHeight(80).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center),
        GridItem(playButtons[0]).withWidth(50).withHeight(50).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center),
        GridItem(playButtons[1]).withWidth(50).withHeight(50).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center),
        GridItem(playButtons[2]).withWidth(50).withHeight(50).withAlignSelf(GridItem::AlignSelf::center).withJustifySelf(GridItem::JustifySelf::center)
    };
    grid.performLayout(r.removeFromTop(r.getHeight() / 2));
    
    nextButton.setBounds(r.removeFromRight(120).removeFromBottom(120));
}
