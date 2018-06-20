/*
 ==============================================================================
 
 FileManager.h
 Created: 6 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Gui/ListboxLookAndFeel.h"
#include "GuiUI.h"

class FileManager  : public TableListBoxModel,
                     public Button::Listener
{
public:
    FileManager (ValueTree& vt, GuiUI& gui);
    ~FileManager();
//==============================================================================
    
    int getNumRows() override;
    void paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
    void cellDoubleClicked (int rowNumber, int columnId, const MouseEvent& event) override;
    void selectedRowsChanged (int lastRowSelected) override;
    
//==============================================================================
    void buttonClicked (Button* button) override;
    
//==============================================================================
    void setStartTime (int, String);
    String getStartTime (int) const;
    
//==============================================================================
    void addFile ();
    void removeFile (int position);
    void clearFileList ();
    
private:
    ValueTree fileTree;
    GuiUI& ui;
    
    int selectedFile;
    
    ListboxLookAndFeel fllaf;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileManager)
};
