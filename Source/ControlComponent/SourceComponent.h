/*
  ==============================================================================

    SourceComponent.h
    Created: 18 Mar 2018 9:19:01pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Definitions.h"
#include "../Core/Shapes.h"
#include "../Gui/ListboxLookAndFeel.h"

class SourceComponent :     public Component,
                            public TableListBoxModel,
                            public ValueTree::Listener
{
public:
    SourceComponent();
    ~SourceComponent();
    //==============================================================================
    
    void paint (Graphics&) override;
    void resized() override;
    //==============================================================================

    int getNumRows() override;
    void paintRowBackground (Graphics&, int, int, int, bool) override;
    void paintCell (Graphics&, int, int, int, int, bool) override;
    Component* refreshComponentForCell (int, int, bool, Component*) override;
    
    void selectedRowsChanged (int) override;
    
    //==============================================================================
    void valueTreePropertyChanged (ValueTree&, const Identifier&) override;
    void valueTreeChildAdded (ValueTree&, ValueTree&) override;
    void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override;
    void valueTreeChildOrderChanged (ValueTree&, int, int) override;
    void valueTreeParentChanged (ValueTree&) override;
    void valueTreeRedirected (ValueTree&) override;

    //==============================================================================
    void addFile();
    void removeFile(int);
    void clearFileList();
    
    void setStartTime (int, String);
    String getStartTime (int) const;
    
    void updateButtonRow();
    void updateSelection();

//==============================================================================
private:
    ValueTree vt;
    ListboxLookAndFeel lookAndFeel;
    
    TableListBox fileListBox;
    DrawableButton addButton, removeButton, clearButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceComponent)
};
