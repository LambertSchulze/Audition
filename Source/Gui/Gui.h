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
#include "AudioFileList.h"
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
    
    // Gui UI
    void repaintGui() override;
    
    void updateFileList() override;
    void selectRowInFileList (int number) override;
    void enableFileSettingButtons() override;
    void disableFileSettingButtons() override;
    bool isDraggingOverList() override;
    
    TransportComponent* getTransportComponent() override;
    void enableOriginalButton() override;
    void enableEffectButton() override;
    void disableEffectButton() override;
    void disableTransportButtons() override;
    
    void turnAllPlayButtonsOff() override;
    void turnOriginalButtonOff() override;
    void turnEffectButtonOff() override;
    void turnOriginalButtonOn() override;
    void turnEffectButtonOn() override;
    
    bool shouldPlayOriginal() override;

    // ==============================================
    void setPage(int page);
    void Register();
    
    AuditionLookAndFeel laf;
    MainMenuLookAndFeel mmlaf;
    ListboxLookAndFeel fllaf;
    
    OwnedArray<TextButton> headerButtons;
    AudioFileList fileList;
    OwnedArray<DrawableButton> fileSettingButtons;
    OwnedArray<Drawable> buttonImages;
    ScopedPointer<StretchableLayoutResizerBar> stretchBar;
    StretchableLayoutManager stretchBarLayout;
    TransportComponent transportComponent;
    OwnedArray<Component> pages;
};
