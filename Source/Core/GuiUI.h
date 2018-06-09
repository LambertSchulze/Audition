/*
 ==============================================================================
 
 GuiUI.h
 Created: 8 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class GuiUI
{
public:
    GuiUI()    {};
    ~GuiUI()   {};
    
    virtual void repaintGui() =0;
    
    virtual void updateFileList() =0;
    virtual void selectRowInFileList (int number) =0;
    
    virtual void enableTransportButtons() =0;
    virtual void disableTransportButtons() =0;
    virtual void enableFileSettingButtons() =0;
    virtual void disableFileSettingButtons() =0;
    
    virtual void turnOriginalButtonOff() =0;
    virtual bool shouldPlayOriginal() =0;
    virtual bool allPlayButtonsOff() =0;
    virtual void turnAllPlayButtonsOff() =0;
};
