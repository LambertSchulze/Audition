/*
  ==============================================================================

    OverviewScreen.cpp
    Created: 18 Mar 2018 9:32:33pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "OverviewScreen.h"
#include "../Definitions/Definitions.h"

//==============================================================================
OverviewScreen::OverviewScreen(ValueTree& vt)
:   mainVT(vt)
{
    effectVT = mainVT.getChildWithName(IDs::EffectList);
    
    for (int child = 0; child < effectVT.getNumChildren(); child++)
    {
        buttonList.add(new TextButton(effectVT.getChild(child).getProperty(IDs::EffectName)));
        addAndMakeVisible(buttonList[child]);
        buttonList[child]->setClickingTogglesState(true);
        buttonList[child]->setRadioGroupId(555);
        buttonList[child]->addListener(this);
    }
}

OverviewScreen::~OverviewScreen()           {}

void OverviewScreen::paint (Graphics& g)    {}

void OverviewScreen::resized()
{
    auto bounds = getLocalBounds();
    
    for (int button = 0; button < buttonList.size(); button++)
    {
        buttonList[button]->setBounds(bounds.removeFromTop(20));
    }
}

void OverviewScreen::buttonClicked (Button* button)
{
    String s = button->getName();
    ValueTree selectedEffect = effectVT.getChildWithProperty(IDs::EffectName, s);
    int selectedEffectNumber = selectedEffect.getProperty(IDs::Number);
    mainVT.getChildWithName(IDs::Transport).setProperty(IDs::EffectToPlay, selectedEffectNumber, nullptr);
}