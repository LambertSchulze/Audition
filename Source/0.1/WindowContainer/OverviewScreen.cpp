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
#include "../Core/TransportManager.h"

//==============================================================================
OverviewScreen::OverviewScreen(ValueTree& vt)
:   tree(vt)
{
    tree = tree.getChildWithName(IDs::EffectList);
    
    for (int child = 1; child < tree.getNumChildren(); child++)
    {
        TextButton* button = new TextButton(tree.getChild(child)[IDs::EffectName].toString());
        addAndMakeVisible(button);
        button->setButtonText(EFFECTLIST.getChild(child)[IDs::EffectName]);
        button->setClickingTogglesState(true);
        button->setRadioGroupId(555);
        button->onClick = [this, child] { TransportManager::instance->setEffect(child); };
        
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
