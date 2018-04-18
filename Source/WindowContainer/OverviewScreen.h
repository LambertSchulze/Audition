/*
  ==============================================================================

    OverviewScreen.h
    Created: 18 Mar 2018 9:32:33pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class OverviewScreen    : public Component
{
public:
    OverviewScreen(ValueTree&);
    ~OverviewScreen();

    void paint (Graphics&) override;
    void resized() override;

private:
    ValueTree mainVT;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OverviewScreen)
};
