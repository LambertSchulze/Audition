/*
 ==============================================================================
 
 TransportManager.cpp
 Created: 1 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "TransportManager.h"

TransportManager::TransportManager (AudioTransportSource& ts, GuiUI& gui)
: transportSource (ts), ui(gui)
{
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    
    if (effectList.isEmpty()) {
        effectList.add(new NoEffect());
        effectList.add(new SumVolumeUp());
        effectList.add(new SumVolumeDown());
        effectList.add(new LeftSolo());
        effectList.add(new RightSolo());
        effectList.add(new Mono());
        effectList.add(new LRSwitched());
        effectList.add(new MidVolumeUp());
        effectList.add(new MidVolumeDown());
        effectList.add(new SideVolumeUp());
        effectList.add(new SideVolumeDown());
    }
}

TransportManager::~TransportManager()
{
    transportSource.removeChangeListener(this);
}

void TransportManager::changeListenerCallback(ChangeBroadcaster* source)
{
    Component* componentBroadcaster = dynamic_cast<Component*>(source);
    
    if (source == &transportSource) {
        transportSource.isPlaying() ? setTransportTo(PLAYING) : setTransportTo(STOPPING);
    }
    
    else if (componentBroadcaster->getName() == "Transport Component") {
        transportComponentClicked();
    }
}

void TransportManager::buttonClicked (Button* button)
{
    if (button->getName().startsWith("Overview Screen Button")) {
        setEffectToPlay(button->getName().getTrailingIntValue());
    }
}

void TransportManager::setTransportSource ()
{
    if (playbackFile.isEmpty()) {
        transportSource.setSource(nullptr);
        return;
    }
    
    auto file = File(playbackFile);
    auto* audioReader = formatManager.createReaderFor(file);
    
    if (audioReader != nullptr) {
        std::unique_ptr<AudioFormatReaderSource> newAudioSource (new AudioFormatReaderSource(audioReader, true));
        transportSource.setSource(newAudioSource.get(), 0, nullptr, audioReader->sampleRate);
        transportSource.setPosition(startTime);
        readerSource.reset (newAudioSource.release());
    }
}

void TransportManager::setTransportTo(const TransportState& transportState)
{
    if (this->transportState != transportState) {
        this->transportState = transportState;
        
        switch (this->transportState) {
            case STARTING:
                setTransportSource();
                transportSource.start();
                setTransportTo(PLAYING);
                break;
                
            case PLAYING:
                break;
                
            case STOPPING:
                transportSource.stop();
                ui.turnAllPlayButtonsOff();
                setTransportTo(STOPPED);
                break;
                
            case STOPPED:
                transportSource.setPosition (startTime);
                break;
        }
    }
    else jassert("setting Transport to the same transprotState shouldn't happen.");
}

TransportState TransportManager::getTransportState()
{
    return transportState;
};

void TransportManager::setEffectPlayback (bool shouldPlayEffect)
{
    isPlayingEffect = shouldPlayEffect;
}

void TransportManager::setEffectToPlay (int effectNumberToPlay)
{
    effectToPlay = effectList[effectNumberToPlay];
}

Effect* TransportManager::getEffectToPlay () const
{
    return effectToPlay;
}


void TransportManager::setPlaybackFile (const String &newfilePath)
{
    playbackFile = newfilePath;
}

String TransportManager::getPlaybackFile()
{
    return playbackFile;
}

void TransportManager::setStartTime (int newStartTime)
{
    startTime = newStartTime;
}

bool TransportManager::shouldPlayEffect() const
{
    return isPlayingEffect;
}

void TransportManager::startPlayingOriginal(const String& filePath, const int& startTime)
{
    setTransportTo(STOPPING);
    
    if (filePath != playbackFile) {
        this->playbackFile = filePath;
    }
    if (startTime != this->startTime) {
        this->startTime = startTime;
    }
    isPlayingEffect = false;
    
    ui.turnOriginalButtonOn();
    setTransportTo(STARTING);
}

void TransportManager::startPlayingWithEffect(const String& filePath, const int& startTime, Effect* effectToPlay)
{
    setTransportTo(STOPPING);
    
    if (filePath != playbackFile) {
        this->playbackFile = filePath;
    }
    if (startTime != this->startTime) {
        this->startTime = startTime;
    }
    if (effectToPlay != this->effectToPlay) {
        this->effectToPlay = effectToPlay;
    }
    isPlayingEffect = true;
    
    ui.turnEffectButtonOn();
    setTransportTo(STARTING);
}

void TransportManager::stopPlayback()
{
    if (!(transportState == STOPPED)) {
        setTransportTo(STOPPING);
    }
}

void TransportManager::transportComponentClicked()
{
    if (ui.shouldPlayOriginal()) {
        if (transportState == STOPPED) {
            ui.turnOriginalButtonOn();
            setTransportTo(STARTING);
        }
        else {
            ui.turnOriginalButtonOff();
            setTransportTo(STOPPING);
        }
    }
}
