/*
 ==============================================================================
 
 WindowContainer.h
 Created: 18 Mar 2018 9:32:08pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Gui/MainMenuLookAndFeel.h"
#include "TitleScreen.h"
#include "OverviewScreen.h"
#include "QuickQuizScreen.h"

//==============================================================================
/*
 */
class WindowContainer   :   public Component,
                            public Button::Listener
{
public:
    WindowContainer(ValueTree&);
    ~WindowContainer();
    
    void paint (Graphics&) override;
    void resized() override;

    void buttonClicked (Button*) override;

private:
    ValueTree vt;
    MainMenuLookAndFeel lookAndFeel;
    
    TitleScreen titleScreen;
    OverviewScreen overviewScreen;
    QuickQuizScreen quickQuizScreen;
    
    TextButton overviewButton, quizButton, statisticsButton, aboutButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowContainer)
};
