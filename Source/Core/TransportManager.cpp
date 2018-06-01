/*
 ==============================================================================
 
 TransportManager.cpp
 Created: 1 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "TransportManager.h"

TransportManager::TransportManager (AudioTransportSource& transportSource)
: transportSource (transportSource)
{
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
}

TransportManager::~TransportManager()
{
    transportSource.removeChangeListener(this);
}

void TransportManager::changeListenerCallback(ChangeBroadcaster *thingThatChanged)
{
    if (thingThatChanged == &transportSource) {
        transportSource.isPlaying() ? setTransportTo(PLAYING) : setTransportTo(STOPPED);
    }
}

void TransportManager::setTransportTo(const TransportState& transportState)
{
    if (this->transportState != transportState) {
        this->transportState = transportState;
        
        switch (this->transportState) {
            case STARTING:
                transportSource.start();
                break;
                
            case PLAYING:
                break;
                
            case STOPPING:
                transportSource.stop();
                break;
                
            case STOPPED:
                transportSource.setPosition (startTime);
                break;
        }
    }
}

void TransportManager::setEffectPlayback(bool shouldPlayEffect)
{
    isPlayingEffect = shouldPlayEffect;
}

void TransportManager::setEffectToPlay(Effect *effectToPlay)
{
    this->effectToPlay = effectToPlay;
}

void TransportManager::setFileForPlayback(String &filePath)
{
    auto file = File(filePath);
    AudioFormatReader* audioReader = formatManager.createReaderFor(file);
    
    if (audioReader != nullptr) {
        ScopedPointer<AudioFormatReaderSource> newAudioSource = new AudioFormatReaderSource(audioReader, true);
        transportSource.setSource(newAudioSource, 0, nullptr, audioReader->sampleRate);
        transportSource.setPosition(startTime);
    }
}

void TransportManager::setStartPosition(int newStartTime)
{
    startTime = newStartTime;
}

Effect* TransportManager::getEffectToPlay()
{
    return effectToPlay;
}

bool TransportManager::shouldPlayEffect()
{
    return isPlayingEffect;
}

void TransportManager::startPlayingOriginal()
{
    if (!(transportState == PLAYING && isPlayingEffect == false)) {
        isPlayingEffect = false;
        setTransportTo(STARTING);
    }
}

void TransportManager::startPlayingWithEffect(Effect *effectToPlay)
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
