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
        effectList.add(new NoEffect()); // Effect number 0 will be an indicator for original playback.
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
    
    effectToPlay = effectList[0];
}

TransportManager::~TransportManager()
{
    transportSource.removeChangeListener(this);
}

void TransportManager::changeListenerCallback(ChangeBroadcaster* source)
{
    Component* componentBroadcaster = dynamic_cast<Component*>(source);
    
    if (source == &transportSource) {
        transportSource.isPlaying() ? setState(PLAYING) : setState(STOPPING);
    }
    
    else if (componentBroadcaster->getName() == "Transport Component") {
        transportComponentClicked();
    }
}

void TransportManager::buttonClicked (Button* button)
{
    if (button->getName().startsWith("Overview Screen Button")) {
        setEffect(button->getName().getTrailingIntValue());
    }
}

void TransportManager::stateChanged()
{
    switch (this->TransportState::state)
    {
        case STARTING_ORIGINAL:
            setTransportSource();
            effectToPlay = effectList[0];
            transportSource.start();
            setState(PLAYING);
            break;
            
        case STARTING_EFFECT:
            setTransportSource();
            effectToPlay = effectList[playbackEffect];
            transportSource.start();
            setState(PLAYING);
            break;
            
        case PLAYING:
            break;
            
        case STOPPING:
            transportSource.stop();
            ui.turnAllPlayButtonsOff();
            setState(STOPPED);
            break;
            
        case STOPPED:
            transportSource.setPosition (this->startTime);
            break;
            
        default:
            DBG("Error in TransportState::state");
            break;
    }
}

void TransportManager::effectChanged ()
{
    if (getEffect() == 0) {
        ui.disableEffectButton();
    }
    else ui.enableEffectButton();    
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

Effect* TransportManager::getEffectToPlay () const
{
    return effectToPlay;
}

void TransportManager::transportComponentClicked()
{
    if (ui.shouldPlayOriginal()) {
        if (getState() == TransportState::STOPPED) {
            //ui.turnOriginalButtonOn();
            setState(STARTING_ORIGINAL);
        }
        else {
            //ui.turnOriginalButtonOff();
            setState(STOPPING);
        }
    }
    
    else if (!ui.shouldPlayOriginal()) {
        if (getState() == TransportState::STOPPED) {
            //ui.turnEffectButtonOn();
            setState(STARTING_EFFECT);
        }
        else {
            //ui.turnEffectButtonOff();
            setState(TransportState::STOPPING);
        }
    }
}
