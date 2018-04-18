/*
  ==============================================================================

    TitleScreen.h
    Created: 18 Mar 2018 9:32:08pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TitleScreen    : public Component
{
public:
    TitleScreen();
    ~TitleScreen();

    void paint (Graphics&) override;
    void resized() override;
    
    void readFile (const File&);
    
private:  
    TextEditor textEditor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TitleScreen)
};