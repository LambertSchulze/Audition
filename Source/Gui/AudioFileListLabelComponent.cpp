/*
 ==============================================================================
 
 AudioFileListLabelComponent.cpp
 Created: 21 Mar 2018 12:28:13pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "AudioFileListLabelComponent.h"
#include "../Definitions/Definitions.h"

//==============================================================================
AudioFileListLabelComponent::AudioFileListLabelComponent(FileManager& sc)
: owner(sc)
{
    setEditable(true, true, false);
    setLookAndFeel(&lookAndFeel);
}

AudioFileListLabelComponent::~AudioFileListLabelComponent()
{
    setLookAndFeel(nullptr);
}

void AudioFileListLabelComponent::textWasEdited()
{
    owner.setStartTime(row, getText());
}

void AudioFileListLabelComponent::setRow(const int newRow)
{
    row = newRow;
    setText(owner.getStartTime(newRow), dontSendNotification);
}
