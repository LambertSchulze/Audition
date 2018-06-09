/*
 ==============================================================================
 
 Gui.h
 Created: 1 Jun 2018 9:32:08pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Core/GuiUI.h"
#include "../Definitions/Definitions.h"

#include "TransportComponent.h"
#include "AuditionLookAndFeel.h"
#include "MainMenuLookAndFeel.h"
#include "ListboxLookAndFeel.h"

struct Gui  : public Component,
              public GuiUI
{
public:
    Gui (ValueTree& tree);
    ~Gui ();
    
    void paint (Graphics& g) override;
    void resized() override;
    
    void repaintGui() override;
    void updateFileList() override;
    void selectRowInFileList (int number) override;
    void enableTransportButtons() override;
    void disableTransportButtons() override;
    void enableFileSettingButtons() override;
    void disableFileSettingButtons() override;
    void turnOriginalButtonOff() override;
    bool shouldPlayOriginal() override;
    bool allPlayButtonsOff() override;
    void turnAllPlayButtonsOff() override;
    
    void setPage(int page);
    void Register();
    
    AuditionLookAndFeel laf;
    MainMenuLookAndFeel mmlaf;
    ListboxLookAndFeel fllaf;
    
    OwnedArray<TextButton> headerButtons;
    TableListBox fileList;
    OwnedArray<DrawableButton> fileSettingButtons;
    OwnedArray<Drawable> buttonImages;
    ScopedPointer<StretchableLayoutResizerBar> stretchBar;
    StretchableLayoutManager stretchBarLayout;
    TransportComponent transportComponent;
    OwnedArray<Component> pages;
};
