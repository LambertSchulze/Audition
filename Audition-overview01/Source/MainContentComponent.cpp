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
:   mainVT(IDs::Main)
{
    auto appDataDir = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Application Support").getChildFile(JUCEApplication::getInstance()->getApplicationName());
    
    if (!appDataDir.exists())
        appDataDir.createDirectory();
    
    settingsFile = appDataDir.getChildFile ("Save");
    
    
    setAudioChannels (2, 2);
    setLookAndFeel(&lookAndFeel);
    
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    setupProperties();
    
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
    saveData(settingsFile);
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
void MainContentComponent::setupProperties()
{
    loadData(settingsFile);
    
    // if VT is not valid, create a new one.
    if (!mainVT.isValid())
    {
        //DBG ("No valid ValueTree..");
        mainVT = ValueTree(IDs::Main);
    }
    
    
    // checking for MAIN properties.
    if (!mainVT.hasProperty(IDs::WindowHeight)) mainVT.setProperty(IDs::WindowHeight, 600, nullptr);
    if (!mainVT.hasProperty(IDs::WindowWidth))  mainVT.setProperty(IDs::WindowWidth, 800, nullptr);
    
    
    // checking for TRANSPORT
    if (!mainVT.getChildWithName(IDs::Transport).isValid())
    {
        // setting up a fresh TRANSPORT child.
        ValueTree transport (IDs::Transport);
        transport.setProperty(IDs::LimitPlayback, false, nullptr);
        mainVT.addChild(transport, -1, nullptr);
    }
    // nulling TRANSPORT
    mainVT.getChildWithName(IDs::Transport).setProperty(IDs::TransportState,    "Stopped",  nullptr);
    mainVT.getChildWithName(IDs::Transport).setProperty(IDs::IsProcessing,      false,      nullptr);
    mainVT.getChildWithName(IDs::Transport).setProperty(IDs::EffectToPlay,      -1,         nullptr);
    
    
    // checking for FILELIST
    if (!mainVT.getChildWithName(IDs::FileList).isValid())
    {
        // setting up a fresh FILELIST child
        ValueTree fileList (IDs::FileList);
        fileList.setProperty(IDs::SelectedFile, 0, nullptr);
        mainVT.addChild(fileList, -1, nullptr);
    }
    
    // checking for EFFECTLIST
    if (!mainVT.getChildWithName(IDs::EffectList).isValid())
    {
        // setting up a new FILELIST with Level 0 Effects
        
        ValueTree effectList    (IDs::EffectList);
        
        ValueTree noEffect      (IDs::Effect);
        noEffect    .setProperty(IDs::Number, 0, nullptr);
        noEffect    .setProperty(IDs::EffectName, "No Effect", nullptr);
        noEffect    .setProperty(IDs::EffectType, "Other", nullptr);
        noEffect    .setProperty(IDs::Level, 0, nullptr);
        ValueTree sumVolUp      (IDs::Effect);
        sumVolUp    .setProperty(IDs::Number, 1, nullptr);
        sumVolUp    .setProperty(IDs::EffectName, "Sum Vol Up", nullptr);
        sumVolUp    .setProperty(IDs::EffectType, "Volume", nullptr);
        sumVolUp    .setProperty(IDs::Level, 0, nullptr);
        ValueTree sumVolDown    (IDs::Effect);
        sumVolDown  .setProperty(IDs::Number, 2, nullptr);
        sumVolDown  .setProperty(IDs::EffectName, "Sum Vol Down", nullptr);
        sumVolDown  .setProperty(IDs::EffectType, "Volume", nullptr);
        sumVolDown  .setProperty(IDs::Level, 0, nullptr);
        ValueTree leftSolo      (IDs::Effect);
        leftSolo    .setProperty(IDs::Number, 3, nullptr);
        leftSolo    .setProperty(IDs::EffectName, "Left Solo", nullptr);
        leftSolo    .setProperty(IDs::EffectType, "Solo", nullptr);
        leftSolo    .setProperty(IDs::Level, 0, nullptr);
        ValueTree rightSolo     (IDs::Effect);
        rightSolo   .setProperty(IDs::Number, 4, nullptr);
        rightSolo   .setProperty(IDs::EffectName, "Right Solo", nullptr);
        rightSolo   .setProperty(IDs::EffectType, "Solo", nullptr);
        rightSolo   .setProperty(IDs::Level, 0, nullptr);
        ValueTree mono          (IDs::Effect);
        mono        .setProperty(IDs::Number, 5, nullptr);
        mono        .setProperty(IDs::EffectName, "Mono", nullptr);
        mono        .setProperty(IDs::EffectType, "Stereo Image", nullptr);
        mono        .setProperty(IDs::Level, 0, nullptr);
        ValueTree lrswitched    (IDs::Effect);
        lrswitched  .setProperty(IDs::Number, 6, nullptr);
        lrswitched  .setProperty(IDs::EffectName, "LR Switched", nullptr);
        lrswitched  .setProperty(IDs::EffectType, "Stereo Image", nullptr);
        lrswitched  .setProperty(IDs::Level, 0, nullptr);
        ValueTree midVolUp      (IDs::Effect);
        midVolUp    .setProperty(IDs::Number, 7, nullptr);
        midVolUp    .setProperty(IDs::EffectName, "Mid Vol Up", nullptr);
        midVolUp    .setProperty(IDs::EffectType, "Volume", nullptr);
        midVolUp    .setProperty(IDs::Level, 0, nullptr);
        ValueTree midVolDown    (IDs::Effect);
        midVolDown  .setProperty(IDs::Number, 8, nullptr);
        midVolDown  .setProperty(IDs::EffectName, "Mid Vol Down", nullptr);
        midVolDown  .setProperty(IDs::EffectType, "Volume", nullptr);
        midVolDown  .setProperty(IDs::Level, 0, nullptr);
        ValueTree sideVolUp      (IDs::Effect);
        sideVolUp   .setProperty(IDs::Number, 9, nullptr);
        sideVolUp   .setProperty(IDs::EffectName, "Side Vol Up", nullptr);
        sideVolUp   .setProperty(IDs::EffectType, "Volume", nullptr);
        sideVolUp   .setProperty(IDs::Level, 0, nullptr);
        ValueTree sideVolDown    (IDs::Effect);
        sideVolDown .setProperty(IDs::Number, 10, nullptr);
        sideVolDown .setProperty(IDs::EffectName, "Side Vol Down", nullptr);
        sideVolDown .setProperty(IDs::EffectType, "Volume", nullptr);
        sideVolDown .setProperty(IDs::Level, 0, nullptr);
        
        effectList.addChild(noEffect,       -1, nullptr);
        effectList.addChild(sumVolUp,       -1, nullptr);
        effectList.addChild(sumVolDown,     -1, nullptr);
        effectList.addChild(leftSolo,       -1, nullptr);
        effectList.addChild(rightSolo,      -1, nullptr);
        effectList.addChild(mono,           -1, nullptr);
        effectList.addChild(lrswitched,     -1, nullptr);
        effectList.addChild(midVolUp,       -1, nullptr);
        effectList.addChild(midVolDown,     -1, nullptr);
        effectList.addChild(sideVolUp,      -1, nullptr);
        effectList.addChild(sideVolDown,    -1, nullptr);
        mainVT.addChild(effectList, -1, nullptr);
    }
    
//    if (!mainVT.getChildWithName(IDs::Quiz).isValid())
//    {
//        ValueTree quizTree (IDs::Quiz);
//        quizTree.setProperty(IDs::QuizState, 3, nullptr);
//        
//        for (int i=0; i<3; ++i)
//        {
//            ValueTree choiceTree (IDs::Choice);
//            choiceTree.setProperty(IDs::Name, "", nullptr);
//            choiceTree.setProperty(IDs::isRight, "", nullptr);
//            quizTree.addChild(choiceTree, -1, nullptr);
//        }
//        mainVT.addChild(quizTree, -1, nullptr);
//    }
//    if (mainVT.getChildWithName(IDs::Quiz).getChildWithProperty(IDs::isRight, true).isValid()) mainVT.getChildWithName(IDs::Quiz).getChildWithProperty(IDs::isRight, true).setProperty(IDs::isRight, false, nullptr);
    
    //DBG ("Property Setup done! Here's the ValueTree:");
    //DBG ("mainVT.toXmlString()");
}

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

void MainContentComponent::loadData(File file)
{
    DBG("Loading Data...");
    if (file.exists())
    {
        ScopedPointer<XmlElement> e (XmlDocument::parse (file));
        
        if (e == NULL)
        {
            mainVT = ValueTree();
            DBG("Loading failed..");
        }
        else
        {
            mainVT = ValueTree::fromXml(*e);
            DBG("...Loading done!");
        }
    }
    else
    {
        DBG("File doesn't exist.");
        Result creation (file.create());
        
        if (creation.wasOk())       DBG("created a new file! Hurray!");
        else                        {DBG("could not create a new file :-(");
                                    DBG(creation.getErrorMessage());}
    }
}

void MainContentComponent::saveData(File file)
{
    if (file.exists())
    {
        ScopedPointer<XmlElement> e (mainVT.createXml());
        e->writeToFile(file, "");
        DBG("Data saved.");
        DBG("This is the saved ValueTree:");
        DBG(mainVT.toXmlString());
    }
    if (!file.exists()) DBG("Save file doesn't exist. Could't save..");
}
