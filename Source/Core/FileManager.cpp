/*
 ==============================================================================
 
 FileManager.cpp
 Created: 6 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileManager.h"
#include "../Gui/AudioFileListLabelComponent.h"
#include "../Definitions/Definitions.h"

FileManager::FileManager (ValueTree& vt, GuiUI& gui)
: fileTree(vt), ui(gui)
{
    fileTree = fileTree.getChildWithName(IDs::FileList);
    
    if (fileTree.getNumChildren() == 0) {
        ui.disableFileSettingButtons();
        ui.disableTransportButtons();
    }
    else {
        ui.enableFileSettingButtons();
        ui.enableOriginalButton();
    }
}

FileManager::~FileManager()
{
    
}

int FileManager::getNumRows()
{
    return fileTree.getNumChildren();
}

void FileManager::paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) g.fillAll (AuditionColours::blue);
    
    else if (rowNumber % 2) g.fillAll (AuditionColours::lightgrey);
    else {
        g.setColour(AuditionColours::lightgrey);
        g.drawVerticalLine(width - 1, 2, height - 2);
    }
}

void FileManager::paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour ((rowIsSelected) ? fllaf.findColour(TableHeaderComponent::highlightColourId) : fllaf.findColour(ListBox::textColourId));
    
    if (fileTree.getChild(rowNumber).isValid())
    {
        if (columnId == 1)
        {
            auto text = fileTree.getChild(rowNumber).getProperty(IDs::FileName);
            g.drawText (text, 14, 0, width - 4, height, Justification::centredLeft, true);
        }
    }
}

Component* FileManager::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {
        auto* timeLabel = static_cast<AudioFileListLabelComponent*>(existingComponentToUpdate);
        
        if (timeLabel == nullptr) timeLabel = new AudioFileListLabelComponent(*this);
        timeLabel->setRow(rowNumber);
        if (isRowSelected) timeLabel->setColour(Label::ColourIds::textColourId, AuditionColours::white);
        else timeLabel->setColour(Label::ColourIds::textColourId, AuditionColours::black);
        return timeLabel;
    }

    return nullptr;
}

void FileManager::cellDoubleClicked (int rowNumber, int columnId, const MouseEvent& event)
{
    const String filePath = fileTree.getChild(rowNumber)[IDs::FilePath];
    const int startTime = fileTree.getChild(rowNumber)[IDs::FileStart];
    
    transport.setState(TransportState::STOPPING);
    transport.setFile(filePath);
    transport.setStart(startTime);
    transport.setState(TransportState::STARTING_ORIGINAL);
}

void FileManager::selectedRowsChanged (int lastRowSelected)
{
    if (fileTree.getNumChildren()) {
        selectedFile = lastRowSelected;
        
        const String filePath = fileTree.getChild(lastRowSelected)[IDs::FilePath];
        transport.setFile(filePath);
        
        const int startTime = fileTree.getChild(lastRowSelected)[IDs::FileStart];
        transport.setStart(startTime);
    }
}

void FileManager::buttonClicked (Button* button)
{
    if (button->getName() == "Add Button")      {addFile();};
    if (button->getName() == "Remove Button")   {removeFile(selectedFile);};
    if (button->getName() == "Clear Button")    {clearFileList();};
}

void FileManager::setStartTime (int row, String startTime)
{
    fileTree.getChild(row).setProperty(IDs::FileStart, startTime, nullptr);
}

String FileManager::getStartTime (int row) const
{
    return fileTree.getChild(row)[IDs::FileStart];
}

void FileManager::addFile()
{
    bool empty = (getNumRows() == 0) ? true : false;
    
    FileChooser chooser ("Select a Wave file to play...", File::getSpecialLocation(File::userMusicDirectory), "*.wav,*.mp3,*.m4a");
    
    if (chooser.browseForMultipleFilesToOpen())
    {
        Array<File> newFiles (chooser.getResults());
        for (int i = 0; i < newFiles.size(); i++)
        {
            if (!fileTree.getChildWithProperty(IDs::FilePath, newFiles[i].getFullPathName()).isValid())
            {
                ValueTree newFile (IDs::File);
                newFile.setProperty(IDs::FilePath, newFiles[i].getFullPathName(), nullptr);
                newFile.setProperty(IDs::FileName, newFiles[i].getFileNameWithoutExtension(), nullptr);
                newFile.setProperty(IDs::FileStart, "0.00", nullptr);
                bool isLossless (newFiles[i].getFileExtension() == ".wav");
                newFile.setProperty(IDs::IsLossless, isLossless, nullptr);
                
                fileTree.addChild(newFile, -1, nullptr);
            }
        }
    }
    
    if (getNumRows() > 0) {
        ui.enableFileSettingButtons();
        ui.enableOriginalButton();
    }

    if (empty || (getNumRows() == 1)) {
        transport.setFile(fileTree.getChild(0)[IDs::FilePath]);
        Timer::callAfterDelay(0.1, [this] { ui.selectRowInFileList(0); });
    }
    
    ui.updateFileList();
    ui.repaintGui();
}

void FileManager::removeFile (int position)
{
    if (fileTree.getChild(position)[IDs::FilePath] == transport.getFilePath()) {
        transport.setState(TransportState::STOPPING);
    }
    
    fileTree.removeChild(position, nullptr);
    ui.selectRowInFileList(jmax(position - 1, 0));
    
    ui.updateFileList();
    if (getNumRows() == 0) {
        ui.disableFileSettingButtons();
        ui.disableTransportButtons();
    }
    
    ui.updateFileList();
    ui.repaintGui();
}

void FileManager::clearFileList()
{
    if (transport.getState() == TransportState::PLAYING)
        transport.setState(TransportState::STOPPING);
    
    fileTree.removeAllChildren(nullptr);
    transport.setFile("");
    
    ui.disableFileSettingButtons();
    ui.disableTransportButtons();
    
    ui.updateFileList();
    ui.repaintGui();
}
