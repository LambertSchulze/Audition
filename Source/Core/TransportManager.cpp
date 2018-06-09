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

void TransportManager::buttonClicked (Button *button)
{
    
}

void TransportManager::setTransportSource ()
{
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
                if (!ui.allPlayButtonsOff()) ui.turnAllPlayButtonsOff();
                
                setTransportTo(STOPPED);
                break;
                
            case STOPPED:
                transportSource.setPosition (startTime);
                break;
        }
    }
}

void TransportManager::setEffectPlayback (bool shouldPlayEffect)
{
    isPlayingEffect = shouldPlayEffect;
}

void TransportManager::setEffectToPlay (Effect *newEffectToPlay)
{
    effectToPlay = newEffectToPlay;
}

void TransportManager::setPlaybackFile (const String &newfilePath)
{
    playbackFile = newfilePath;
}

void TransportManager::setStartTime (int newStartTime)
{
    startTime = newStartTime;
}

Effect* TransportManager::getEffectToPlay () const
{
    return effectToPlay;
}

bool TransportManager::shouldPlayEffect() const
{
    return isPlayingEffect;
}

void TransportManager::startPlayingOriginal(const String& filePath, const int& startTime)
{
    if (filePath != playbackFile) {
        this->playbackFile = filePath;
    }
    if (startTime != this->startTime) {
        this->startTime = startTime;
    }
    isPlayingEffect = false;
    
    setTransportTo(STOPPING);
    setTransportTo(STARTING);
}

void TransportManager::startPlayingWithEffect(const String& filePath, const int& startTime, Effect* effectToPlay)
{
    if (!(transportState == PLAYING && isPlayingEffect == true && this->effectToPlay == effectToPlay)) {
        this->effectToPlay = effectToPlay;
        isPlayingEffect = true;
        setTransportTo(STARTING);
    }
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
            setTransportTo(STARTING);
        }
        else {
            setTransportTo(STOPPING);
        }
    }
}
