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

struct Gui  : public Component
{
public:
    Gui (ValueTree& tree);
    ~Gui ();
    
    void paint (Graphics& g) override;
    void resized() override;
    
    void setPage(int page);
    void hoockToParentObjects();
    
    AuditionLookAndFeel laf;
    MainMenuLookAndFeel mmlaf;
    ListboxLookAndFeel fllaf;
    
    OwnedArray<TextButton> headerButtons;
    TableListBox fileList;
    OwnedArray<DrawableButton> fileSettingButtons;
    OwnedArray<Drawable> buttonImages;
    ScopedPointer<StretchableLayoutResizerBar> stretchBar;
    StretchableLayoutManager stretchBarLayout;
    OwnedArray<Component> pages;
};
