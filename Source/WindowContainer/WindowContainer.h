/*
 ==============================================================================
 
 WindowContainer.h
 Created: 18 Mar 2018 9:32:08pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TitleScreen.h"
#include "OverviewScreen.h"
#include "QuizScreen.h"

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
    
    TitleScreen titleScreen;
    OverviewScreen overviewScreen;
    QuizScreen quizScreen;
    
    TextButton overviewButton, quizButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowContainer)
};
