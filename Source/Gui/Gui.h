/*
 ==============================================================================
 
 Gui.h
 Created: 1 Jun 2018 9:32:08pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "AuditionLookAndFeel.h"
#include "MainMenuLookAndFeel.h"

class Gui  : public Component
{
public:
    Gui();
    ~Gui();
    
    void paint (Graphics& g) override;
    void resized() override;
    
    void setupAreas();
    
private:
    AuditionLookAndFeel laf;
    MainMenuLookAndFeel mmlaf;
    
    OwnedArray<TextButton> headerButtons;
};
