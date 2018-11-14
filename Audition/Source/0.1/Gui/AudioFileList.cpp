/*
 ==============================================================================
 
 AudioFileList.cpp
 Created: 1 Jul 2018 9:31:32pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "AudioFileList.h"
#include "../Definitions/Definitions.h"
#include "../MainContentComponent.h"
#include "../Core/FileManager.h"

AudioFileList::AudioFileList (const String& name)
    : TableListBox (name, nullptr)
{};

AudioFileList::~AudioFileList()
{};

void AudioFileList::paint (Graphics& g)
{
    g.setColour(AuditionColours::blue);
    
    if (filesAreAbove) {
        g.drawRect(getLocalBounds().withTrimmedTop(this->getRowHeight()), 3);
    }
};

bool AudioFileList::isInterestedInFileDrag (const StringArray& files)
{
    DBG("is interested");
    return true;
};

void AudioFileList::fileDragEnter(const StringArray& files, int x, int y)
{
    DBG("Files Enter");
    filesAreAbove = true;
    repaint();
};

void AudioFileList::fileDragExit(const StringArray& files)
{
    DBG("Files Exit");
    filesAreAbove = false;
    repaint();
};

void AudioFileList::filesDropped (const StringArray &files, int x, int y)
{
    DBG("FilesDropped");
    
    auto* ptr = this->getParentComponent();
    auto* owner = dynamic_cast<MainContentComponent*>(ptr);
    
    for (String filepath : files) {
        File newFile = File(filepath);
        owner->fileManager.addFile(newFile);
    }
    
    filesAreAbove = false;
    repaint();
};
