/*
  ==============================================================================

    SourceComponent.cpp
    Created: 18 Mar 2018 9:19:01pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "SourceComponent.h"
#include "../Gui/AudioFileListLabelComponent.h"

//==============================================================================
SourceComponent::SourceComponent(ValueTree& tree)
:   vt(tree),
    fileListBox {{}, this},
    addButton("Add", DrawableButton::ButtonStyle::ImageOnButtonBackground),
    removeButton("Remove", DrawableButton::ButtonStyle::ImageOnButtonBackground),
    clearButton("Clear", DrawableButton::ButtonStyle::ImageOnButtonBackground)
{
    ScopedPointer<Drawable> addImage    = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_add_black_48px.svg"));
    ScopedPointer<Drawable> removeImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_remove_black_48px.svg"));
    ScopedPointer<Drawable> clearImage  = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_clear_black_48px.svg"));
    
    addAndMakeVisible (&fileListBox);
    addAndMakeVisible (&addButton);
    addAndMakeVisible (&removeButton);
    addAndMakeVisible (&clearButton);
    fileListBox             .setLookAndFeel(&lookAndFeel);
    fileListBox.getHeader() .setLookAndFeel(&lookAndFeel);
    addButton               .setLookAndFeel(&lookAndFeel);
    removeButton            .setLookAndFeel(&lookAndFeel);
    clearButton             .setLookAndFeel(&lookAndFeel);
    
    fileListBox.getHeader().addColumn("Filename", 1, 150, 100, -1, (TableHeaderComponent::visible | TableHeaderComponent::resizable));
    fileListBox.getHeader().addColumn("Start", 2, 48, 48, 48, TableHeaderComponent::visible);
    fileListBox.getHeader().setStretchToFitActive(true);
    fileListBox.setMultipleSelectionEnabled(false);
    
    fileListBox.getHeader().Component::setSize(this->getWidth(), fileListBox.getRowHeight());
//    fileListBox.getVerticalScrollBar().setAutoHide(false);
    
    addButton.      setConnectedEdges(Button::ConnectedOnRight);
    removeButton.   setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    clearButton.    setConnectedEdges(Button::ConnectedOnLeft);
    addButton.      setImages(addImage);
    removeButton.   setImages(removeImage);
    clearButton.    setImages(clearImage);
    
    addButton.      onClick = [this] { addFile(); };
    removeButton.   onClick = [this] { removeFile(fileListBox.getSelectedRow()); };
    clearButton.    onClick = [this] { clearFileList(); };
    
    vt.addListener(this);
    updateButtonRow();
}

SourceComponent::~SourceComponent()
{
    vt.removeListener(this);
}
//==============================================================================

void SourceComponent::paint (Graphics& g)
{
    const int rowHeight (fileListBox.getRowHeight());
    auto r (getLocalBounds());
    auto buttonrowArea (r.removeFromBottom(UI::fileListButtonRowHeight));
    auto emptyArea (r.withTrimmedTop(rowHeight * getNumRows()));
    
    // draw borders of button row
    g.setColour(lookAndFeel.laf.lightergrey);
    g.fillRect(buttonrowArea.removeFromTop(1));
    g.fillRect(buttonrowArea.removeFromRight(1).withTrimmedTop(2).withTrimmedBottom(3));
    
    // draw alternating colourd rows in the whitespace beneath the fileListBox
    g.setColour(lookAndFeel.altRowColour);
    if (!(fileListBox.getNumRows() % 2)) g.fillRect(emptyArea.removeFromTop(rowHeight));
    while (!emptyArea.isEmpty()) {
        g.fillRect(emptyArea.removeFromTop(rowHeight).removeFromRight(1).withTrimmedTop(2).withTrimmedBottom(2));
        g.fillRect(emptyArea.removeFromTop(rowHeight));
    }
    
    if (getNumRows() < 1) {
        g.setColour(lookAndFeel.bgTextColour);
        g.drawText("Add an audio file to start listening.", 0, (getHeight() / (2*rowHeight))*rowHeight, getWidth(), rowHeight, Justification::horizontallyCentred);
    }
}

void SourceComponent::resized()
{
    auto r (getLocalBounds());
    auto buttonRow (r.removeFromBottom(UI::fileListButtonRowHeight).reduced(14, 5));

    addButton      .setBounds(buttonRow.removeFromLeft(UI::fileListButtonWidth));
    removeButton   .setBounds(buttonRow.removeFromLeft(UI::fileListButtonWidth));
    clearButton    .setBounds(buttonRow.removeFromRight(UI::fileListButtonWidth));
    fileListBox    .setBounds(r);
}

//==============================================================================
int SourceComponent::getNumRows()           {return FILELIST.getNumChildren();}

void SourceComponent::paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) g.fillAll (lookAndFeel.highlightedRowColour);
    
    else if (rowNumber % 2) g.fillAll (lookAndFeel.altRowColour);
    else {
        g.setColour(lookAndFeel.altRowColour);
        g.drawVerticalLine(width - 1, 2, height - 2);
    }
}

void SourceComponent::paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour ((rowIsSelected) ? lookAndFeel.findColour(TableHeaderComponent::highlightColourId) : lookAndFeel.findColour(ListBox::textColourId));
    if (FILELIST.getChild(rowNumber).isValid())
    {        
        if (columnId == 1)
        {
            auto text = FILELIST.getChild(rowNumber).getProperty(IDs::FileName);
            g.drawText (text, 14, 0, width - 4, height, Justification::centredLeft, true);
        }
    }
}

Component* SourceComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {
        auto* timeLabel = static_cast<AudioFileListLabelComponent*>(existingComponentToUpdate);
        
        if (timeLabel == nullptr) timeLabel = new AudioFileListLabelComponent(*this);
        timeLabel->setRow(rowNumber);
        if (isRowSelected) timeLabel->setColour(Label::ColourIds::textColourId, lookAndFeel.laf.white);
        else timeLabel->setColour(Label::ColourIds::textColourId, lookAndFeel.laf.black);
        return timeLabel;
    }
    //jassert (existingComponentToUpdate == nullptr);
    return nullptr;
}

void SourceComponent::selectedRowsChanged (int lastRowSelected)
{
    if (FILELIST.getNumChildren())  { FILELIST.setProperty(IDs::SelectedFile, lastRowSelected, nullptr); }
}

//==============================================================================
void SourceComponent::valueTreePropertyChanged (ValueTree& tree, const Identifier& property)
{
    if (property == IDs::SelectedFile)
        updateSelection();
};
void SourceComponent::valueTreeChildAdded (ValueTree&, ValueTree&) {};
void SourceComponent::valueTreeChildRemoved (ValueTree&, ValueTree&, int) {};
void SourceComponent::valueTreeChildOrderChanged (ValueTree&, int, int) {};
void SourceComponent::valueTreeParentChanged (ValueTree&) {};
void SourceComponent::valueTreeRedirected (ValueTree&) {};


//==============================================================================
void SourceComponent::addFile()
{
    FileChooser chooser ("Select a Wave file to play...", File::nonexistent, "*.wav,*.mp3,*.m4a");
    //FileChooser chooser {"Test"};
    
    if (chooser.browseForMultipleFilesToOpen())
    {
        Array<File> newFiles (chooser.getResults());
        for (int i = 0; i < newFiles.size(); i++)
        {
            if (!FILELIST.getChildWithProperty(IDs::FilePath, newFiles[i].getFullPathName()).isValid())
            {
                ValueTree newFile (IDs::File);
                newFile.setProperty(IDs::FilePath, newFiles[i].getFullPathName(), nullptr);
                newFile.setProperty(IDs::FileName, newFiles[i].getFileNameWithoutExtension(), nullptr);
                newFile.setProperty(IDs::FileStart, "0.00", nullptr);
                bool isLossless (newFiles[i].getFileExtension() == ".wav");
                newFile.setProperty(IDs::IsLossless, isLossless, nullptr);
                
                FILELIST.addChild(newFile, -1, nullptr);
            }
        }
    }
    
    updateButtonRow();
}

void SourceComponent::removeFile(int fileIndex)
{
    // check if removed file is playing
    if (fileIndex == (int) FILELIST.getProperty(IDs::SelectedFile)) {
        // stopping playback
        TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);}
    
    FILELIST.removeChild(fileIndex, nullptr);
    fileListBox.selectRow(jmax(fileIndex - 1, 0));
    fileListBox.updateContent();
    updateButtonRow();
}

void SourceComponent::clearFileList()
{
    // check if playback is running
    String s = TRANSPORT.getProperty(IDs::TransportState);
    if (s == "Playing") TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
    
    FILELIST.removeAllChildren(nullptr);
    fileListBox.updateContent();
    updateButtonRow();
}

void SourceComponent::setStartTime (int row, String startTime)
{
    FILELIST.getChild(row).setProperty(IDs::FileStart, startTime, nullptr);
}

String SourceComponent::getStartTime (int row) const
{
    return FILELIST.getChild(row).getProperty(IDs::FileStart);
}

void SourceComponent::updateButtonRow()
{
    if (getNumRows() == 0) {
        removeButton   .setEnabled(false);
        clearButton    .setEnabled(false);}
    
    else if (getNumRows() > 0) {
        removeButton   .setEnabled(true);
        clearButton    .setEnabled(true);}
    repaint();
}

void SourceComponent::updateSelection()
{
    fileListBox.updateContent();
    int rowToSelect = FILELIST[IDs::SelectedFile];
    fileListBox.selectRow (rowToSelect, true, true);
}
