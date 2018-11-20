/*
 ==============================================================================
 
 GuiUI.h
 Created: 8 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Gui/TransportComponent.h"

class GuiUI
{
public:
    GuiUI()    {};
    virtual ~GuiUI()   {};
    
    // general Gui UI
    virtual void repaintGui() =0;
    
    // FileList UI
    virtual void updateFileList() =0;
    virtual void selectRowInFileList (int number) =0;
    virtual void enableFileSettingButtons() =0;
    virtual void disableFileSettingButtons() =0;
    virtual bool isDraggingOverList() =0;
    
    // Transport UI
    virtual TransportComponent* getTransportComponent() =0;
    virtual void enableOriginalButton() =0;
    virtual void enableEffectButton() =0;
    virtual void disableEffectButton() =0;
    virtual void disableTransportButtons() =0;
    
    virtual void turnAllPlayButtonsOff() =0;
    virtual void turnOriginalButtonOff() =0;
    virtual void turnEffectButtonOff() =0;
    virtual void turnOriginalButtonOn() =0;
    virtual void turnEffectButtonOn() =0;
    
    virtual bool shouldPlayOriginal() =0;
};
