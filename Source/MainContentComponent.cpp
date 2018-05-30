/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainContentComponent.h"
#include "Definitions/Definitions.h"

//==============================================================================
MainContentComponent::MainContentComponent()
:   vt()
{
    setAudioChannels (2, 2);
    setLookAndFeel(&lookAndFeel);
    
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    
    if (effectList.isEmpty())
    {
        effectList  .add(new NoEffect());
        effectList  .add(new SumVolumeUp());
        effectList  .add(new SumVolumeDown());
        effectList  .add(new LeftSolo());
        effectList  .add(new RightSolo());
        effectList  .add(new Mono());
        effectList  .add(new LRSwitched());
        effectList  .add(new MidVolumeUp());
        effectList  .add(new MidVolumeDown());
        effectList  .add(new SideVolumeUp());
        effectList  .add(new SideVolumeDown());
    }
    currentEffect = effectList[0];
    shouldProcessEffect = false;
    
    vt = dataHandler.getValueTree();
    vt.addListener(this);
    
    controlComponent    = new ControlComponent(vt);
    windowContainer     = new WindowContainer(vt);
    addAndMakeVisible(controlComponent);
    addAndMakeVisible(windowContainer);
    controlComponent->setInterceptsMouseClicks(false, true);
    windowContainer ->setInterceptsMouseClicks(false, true);
    
    setSize(vt.getProperty(IDs::WindowWidth), vt.getProperty(IDs::WindowHeight));
}

MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
    vt.removeListener(this);
    transportSource.removeChangeListener(this);
    setLookAndFeel (nullptr);
}

void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    transportSource.getNextAudioBlock (bufferToFill);
    transportSource.setGain(Decibels::decibelsToGain(-3));
    
    if (shouldProcessEffect)
    {
        currentEffect->processEffect(bufferToFill);
        //DBG ("giving the processing to an Effect.");
    }
    
    //DBG ("End of getNextAudioBlock()");
}

void MainContentComponent::releaseResources()
{
    transportSource.releaseResources();
}

void MainContentComponent::paint (Graphics& g) {}

void MainContentComponent::resized()
{
    auto r (getLocalBounds());
    controlComponent->setBounds(r);
    windowContainer ->setBounds(r);
    
    vt.setProperty(IDs::WindowHeight, this->getHeight(), nullptr);
    vt.setProperty(IDs::WindowWidth, this->getWidth(), nullptr);
}

//==============================================================================
void MainContentComponent::valueTreePropertyChanged (ValueTree& changedTree, const Identifier& property)
{
    if (changedTree.getType() == IDs::Transport) {
        transportChanged();
    }
}

void MainContentComponent::valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded) {}
void MainContentComponent::valueTreeChildRemoved (ValueTree &parentTree, ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) {}
void MainContentComponent::valueTreeChildOrderChanged (ValueTree &parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) {}
void MainContentComponent::valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged) {}
void MainContentComponent::valueTreeRedirected (ValueTree &treeWhichHasBeenChanged) {}

void MainContentComponent::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        transportSource.isPlaying() ? TRANSPORT.setProperty(IDs::TransportState, "Playing", nullptr) : TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
    }
}

//==============================================================================
void MainContentComponent::setReaderSource (String filePathToSet)
{
    auto file = File(filePathToSet);
    AudioFormatReader* reader = formatManager.createReaderFor(file);
    if (reader != nullptr)
    {
        ScopedPointer<AudioFormatReaderSource> newSource = new AudioFormatReaderSource(reader, true);
        transportSource.setSource(newSource, 0, nullptr, reader->sampleRate);
        int startPosition = FILELIST.getChild(FILELIST.getProperty(IDs::SelectedFile)).getProperty(IDs::FileStart);
        transportSource.setPosition(startPosition);
        readerSource = newSource.release();
    }
}

void MainContentComponent::transportChanged()
// gets called when Properties in the TRANSPORT node change.
// sets the transportSource and the processed Effect.
{
    var tS = TRANSPORT[IDs::TransportState];
    
    if (tS == "Stopped") {
        transportSource.setPosition(0);
    }
    
    if (tS == "Starting") {
        //setting readerSource to the last selected file
        int selectedFile = FILELIST.getProperty(IDs::SelectedFile);
        String filePath = FILELIST.getChild(selectedFile).getProperty(IDs::FilePath);
        setReaderSource(filePath);
        
        transportSource.start();
        TRANSPORT.setProperty(IDs::TransportState, "Playing", nullptr);
    }
    
    if (tS == "Playing") {
        //nothing to do while playback...
    }
    
    if (tS == "Stopping") {
        transportSource.stop();
        TRANSPORT.setProperty(IDs::TransportState, "Stopped", nullptr);
    }
    
    shouldProcessEffect = TRANSPORT[IDs::IsProcessing];
    currentEffect = effectList[(int) TRANSPORT[IDs::EffectToPlay]];
    //DBG ("Effect to play: " + EFFECTLIST.getChild((int) TRANSPORT[IDs::EffectToPlay])[IDs::EffectName].toString());
}
