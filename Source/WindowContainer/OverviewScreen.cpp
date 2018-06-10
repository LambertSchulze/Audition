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
OverviewScreen::OverviewScreen(ValueTree& tree)
:   vt(tree)
{
    for (int child = 0; child < EFFECTLIST.getNumChildren(); child++)
    {
        TextButton* button = new TextButton("Overview Screen Button " + String(child));
        addAndMakeVisible(button);
        button->setButtonText(EFFECTLIST.getChild(child)[IDs::EffectName]);
        button->setClickingTogglesState(true);
        button->setRadioGroupId(555);
        buttonList.add(button);
    }
}

OverviewScreen::~OverviewScreen()           {}

void OverviewScreen::paint (Graphics& g)    {}

void OverviewScreen::resized()
{
    auto bounds = getLocalBounds();
    
    for (int button = 0; button < buttonList.size(); button++)
    {
        buttonList[button]->setBounds(bounds.removeFromTop(20).withSizeKeepingCentre(300, 20));
    }
}
