/*
  ==============================================================================

    SourceComponent.cpp
    Created: 18 Mar 2018 9:19:01pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "SourceComponent.h"
#include "../Definitions/Definitions.h"
#include "../Gui/AudioFileListLabelComponent.h"

//==============================================================================
SourceComponent::SourceComponent(ValueTree& vt)
:   fileListNode(vt),
    addButton("Add", DrawableButton::ButtonStyle::ImageOnButtonBackground),
    removeButton("Remove", DrawableButton::ButtonStyle::ImageOnButtonBackground),
    clearButton("Clear", DrawableButton::ButtonStyle::ImageOnButtonBackground)
{
    fileListNode = fileListNode.getChildWithName(IDs::FileList);
    
    ScopedPointer<Drawable> addImage    = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/ic_add_black_48px.svg"));
    ScopedPointer<Drawable> removeImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/ic_remove_black_48px.svg"));
    ScopedPointer<Drawable> clearImage  = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/ic_clear_black_48px.svg"));
    
    addAndMakeVisible (&fileListBox);
    addAndMakeVisible (addButton);
    addAndMakeVisible (removeButton);
    addAndMakeVisible (clearButton);
    
    fileListBox.getHeader().addColumn("Filename", 1, 150, 100, -1, (TableHeaderComponent::visible | TableHeaderComponent::resizable));
    fileListBox.getHeader().addColumn("Start", 2, 40, 40, 40, TableHeaderComponent::visible);
    fileListBox.getHeader().setStretchToFitActive(true);
    fileListBox.setMultipleSelectionEnabled(false);
    
    addButton.      setConnectedEdges(Button::ConnectedOnRight);
    removeButton.   setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    clearButton.    setConnectedEdges(Button::ConnectedOnLeft);
    
    addButton.      onClick = [this] { addFile(); };
    removeButton.   onClick = [this] { removeFile(fileListBox.getSelectedRow()); };
    clearButton.    onClick = [this] { clearFileList(); };
    
    addButton.      setImages(addImage);
    removeButton.   setImages(removeImage);
    clearButton.    setImages(clearImage);
    
    updateButtons();
}

SourceComponent::~SourceComponent()         {}
//==============================================================================

void SourceComponent::paint (Graphics& g)   {}

void SourceComponent::resized()
{
    auto r (getLocalBounds());
    auto buttonRow (r.removeFromBottom(29).reduced(5));
    addButton      .setBounds(buttonRow.removeFromLeft(buttonRow.getWidth() / 3));
    removeButton   .setBounds(buttonRow.removeFromLeft(buttonRow.getWidth() / 2));
    clearButton    .setBounds(buttonRow);
    fileListBox    .setBounds(r);
}

//==============================================================================
int SourceComponent::getNumRows()           {return fileListNode.getNumChildren();}

void SourceComponent::paintRowBackground (Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour (ListBox::backgroundColourId).interpolatedWith (getLookAndFeel().findColour (ListBox::textColourId), 0.03f);
    if (rowIsSelected)              g.fillAll (Colours::lightblue);
    else if (rowNumber % 2)         g.fillAll (alternateColour);
}

void SourceComponent::paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour ((rowIsSelected) ? Colours::black : getLookAndFeel().findColour (ListBox::textColourId));
    if (fileListNode.getChild(rowNumber).isValid())
    {        
        if (columnId == 1)
        {
            auto text = fileListNode.getChild(rowNumber).getProperty(IDs::FileName);
            g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
        }
    }
    g.setColour (getLookAndFeel().findColour (ListBox::backgroundColourId));
    g.fillRect (width - 1, 0, 1, height);
}

Component* SourceComponent::refreshComponentForCell (int rowNumber, int columnId, bool /*isRowSelected*/, Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {
        auto* timeLabel = static_cast<AudioFileListLabelComponent*>(existingComponentToUpdate);
        
        if (timeLabel == nullptr) timeLabel = new AudioFileListLabelComponent(*this);
        timeLabel->setRow(rowNumber);
        return timeLabel;
    }
    jassert (existingComponentToUpdate == nullptr);
    return nullptr;
}

void SourceComponent::selectedRowsChanged (int lastRowSelected)
{
    if (fileListNode.getNumChildren())
    {
//        fileListNode.getChildWithProperty(IDs::Selected, true).removeProperty(IDs::Selected, nullptr);
//        fileListNode.getChild(fileListBox.getSelectedRow()).setProperty(IDs::Selected, true, nullptr);
        
        fileListNode.setProperty(IDs::SelectedFile, lastRowSelected, nullptr);
    }
}

//==============================================================================
void SourceComponent::addFile()
{
    FileChooser chooser ("Select a Wave file to play...", File::nonexistent, "*.wav,*.mp3,*.m4a");
    
    if (chooser.browseForMultipleFilesToOpen())
    {
        Array<File> newFiles (chooser.getResults());
        for (int i = 0; i < newFiles.size(); i++)
        {
            if (!fileListNode.getChildWithProperty(IDs::FilePath, newFiles[i].getFullPathName()).isValid())
            {
                ValueTree newFile (IDs::File);
                newFile.setProperty(IDs::FilePath, newFiles[i].getFullPathName(), nullptr);
                newFile.setProperty(IDs::FileName, newFiles[i].getFileNameWithoutExtension(), nullptr);
                newFile.setProperty(IDs::FileStart, "0.00", nullptr);
                bool isLossless (newFiles[i].getFileExtension() == ".wav");
                newFile.setProperty(IDs::IsLossless, isLossless, nullptr);
                
                fileListNode.addChild(newFile, -1, nullptr);
            }
        }
    }
    
    fileListBox.updateContent();
    updateButtons();
}

void SourceComponent::removeFile(int fileIndex)
{
    fileListNode.removeChild(fileIndex, nullptr);
    fileListBox.selectRow(jmax(fileIndex - 1, 0));
    fileListBox.updateContent();
    updateButtons();
}

void SourceComponent::clearFileList()
{
    fileListNode.removeAllChildren(nullptr);
    fileListBox.updateContent();
    updateButtons();
}

void SourceComponent::setStartTime (int row, String startTime)
{
    fileListNode.getChild(row).setProperty(IDs::FileStart, startTime, nullptr);
}

String SourceComponent::getStartTime (int row) const
{
    return fileListNode.getChild(row).getProperty(IDs::FileStart);
}

void SourceComponent::updateButtons()
{
    if (getNumRows() == 0) {
        removeButton   .setEnabled(false);
        clearButton    .setEnabled(false);}
    
    else if (getNumRows() > 0) {
        removeButton   .setEnabled(true);
        clearButton    .setEnabled(true);}
    
    if ((fileListBox.getNumSelectedRows() == 0) & (getNumRows() > 0)) fileListBox.selectRow(0, false, false);
}
