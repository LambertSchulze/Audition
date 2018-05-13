/*
 ==============================================================================
 
 AudioFileListLabelComponent.h
 Created: 21 Mar 2018 12:28:13pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Gui/ListboxLookAndFeel.h"
#include "../ControlComponent/SourceComponent.h"

//==============================================================================
/*
 */
class AudioFileListLabelComponent : public Label
{
public:
    AudioFileListLabelComponent(SourceComponent&);
    ~AudioFileListLabelComponent();
    
    void textWasEdited() override;
    void setRow (const int);
    
private:
    SourceComponent& owner;
    int row;
    
    ListboxLookAndFeel lookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFileListLabelComponent)
};
