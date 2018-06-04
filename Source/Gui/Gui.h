/*
 ==============================================================================
 
 Gui.h
 Created: 1 Jun 2018 9:32:08pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Definitions.h"

#include "AuditionLookAndFeel.h"
#include "MainMenuLookAndFeel.h"
#include "ListboxLookAndFeel.h"

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
    ListboxLookAndFeel fllaf;
    
    OwnedArray<TextButton> headerButtons;
    TableListBox fileList;
    OwnedArray<DrawableButton> fileSettingButtons;
    OwnedArray<Drawable> buttonImages;
    
    ScopedPointer<StretchableLayoutResizerBar> stretchBar;
    StretchableLayoutManager stretchBarLayout;
};
