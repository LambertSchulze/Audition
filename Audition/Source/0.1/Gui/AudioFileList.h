/*
 ==============================================================================
 
 AudioFileList.h
 Created: 1 Jul 2018 9:32:08pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class AudioFileList : public TableListBox,
                      public FileDragAndDropTarget
{
public:
    AudioFileList (const String& name);
    ~AudioFileList();
    
    void paint (Graphics& g) override;
    
    bool isInterestedInFileDrag (const StringArray& files) override;
    void fileDragEnter (const StringArray &files, int x, int y) override;
    void fileDragExit (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override;
    
    bool filesAreAbove = false;
};
