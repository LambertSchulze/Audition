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
:   mainVT()
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
    
    mainVT = dataHandler.getValueTree();
    mainVT.addListener(this);
    
    controlComponent    = new ControlComponent(mainVT);
    windowContainer     = new WindowContainer(mainVT);
    addAndMakeVisible(controlComponent);
    addAndMakeVisible(windowContainer);
    controlComponent->setInterceptsMouseClicks(false, true);
    windowContainer ->setInterceptsMouseClicks(false, true);
    
    setSize(mainVT.getProperty(IDs::WindowWidth, 800), mainVT.getProperty(IDs::WindowHeight, 600));
}

MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
    mainVT.removeListener(this);
    transportSource.removeChangeListener(this);
    setLookAndFeel (nullptr);

    DBG ("End of Destructor");
}

void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
    
    DBG ("inside prepareToPlay()");
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

void MainContentComponent::paint (Graphics& g)
{
    ColourGradient backgroundGradient = ColourGradient(Colours::whitesmoke, 0, 0, Colours::lightgrey, 0, getLocalBounds().getHeight(), false);
    g.setGradientFill (backgroundGradient);
    g.fillAll();
    g.setColour (Colours::white);
    g.fillRect(UI::sidebarWidth, UI::headerHeight, getLocalBounds().getWidth()-UI::sidebarWidth, getLocalBounds().getHeight()-UI::headerHeight-UI::footerHeight);
}

void MainContentComponent::resized()
{
    auto r (getLocalBounds());
    controlComponent->setBounds(r);
    windowContainer ->setBounds(r);
    
    mainVT.setProperty(IDs::WindowHeight, this->getHeight(), nullptr);
    mainVT.setProperty(IDs::WindowWidth, this->getWidth(), nullptr);
}

//==============================================================================
void MainContentComponent::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    if (property == IDs::TransportState)
    {
        var tS = treeWhosePropertyHasChanged.getProperty(property);
        if (tS == "Stopped")
        {
            
            //transportSource.setPosition(mainVT.getChildWithName(IDs::FileList).getChild(<#int index#>).getProperty(IDs::Start));
        }
        if (tS == "Starting")   {transportSource.start();
                                treeWhosePropertyHasChanged.setProperty(IDs::TransportState, "Playing", nullptr);}
        if (tS == "Playing")    {}
        if (tS == "Stopping")   {transportSource.stop();
                                treeWhosePropertyHasChanged.setProperty(IDs::TransportState, "Stopped", nullptr);}
    }
    
//    if (property == IDs::forPlayback)
//    {
//        if (treeWhosePropertyHasChanged.getProperty(property)) currentEffect = effectList[(int) treeWhosePropertyHasChanged.getProperty(IDs::Number)];
//        //DBG ("setting an effect for playback.");
//    }
    
    if (property == IDs::EffectToPlay)
    {
        currentEffect = effectList[(int) treeWhosePropertyHasChanged.getProperty(property)];
        DBG (treeWhosePropertyHasChanged.getProperty(property).toString());
    }
    
    if (property == IDs::IsProcessing)
    {
        shouldProcessEffect = treeWhosePropertyHasChanged.getProperty(property);
    }
    
//    if (property == IDs::Selected)
//    {
//        if ((bool) treeWhosePropertyHasChanged.getProperty(property)) setReaderSource(treeWhosePropertyHasChanged.getProperty(IDs::FilePath));
//    }
    
//    if (property == IDs::FileStart)
//    {
//        transportSource.setPosition(mainVT.getChildWithName(IDs::FileList).getChildWithProperty(IDs::Selected, true).getProperty(IDs::Start));
//    }
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
        transportSource.isPlaying() ? mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Playing", nullptr) : mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState, "Stopping", nullptr);
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
        //transportSource.setPosition(mainVT.getChildWithName(IDs::FileList).getChildWithProperty(IDs::Selected, true).getProperty(IDs::Start));
        readerSource = newSource.release();
    }
    DBG ("Set ReaderSource to "<< filePathToSet);
}
