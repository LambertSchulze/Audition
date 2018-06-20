/*
 ==============================================================================
 
 TransportManager.cpp
 Created: 1 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "TransportManager.h"
#include "../Definitions/Definitions.h"

TransportManager* TransportManager::instance = nullptr;

TransportManager::TransportManager (ValueTree& v, AudioTransportSource& ts, GuiUI& gui)
: vt(v), transportSource (ts), ui(gui)
{
    TransportManager::instance = this;
    
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    
    if (effectList.isEmpty()) {
        auto null = ValueTree(IDs::Effect);
        effectList.add(new NoEffect(null));
                
        for (int i = 0; i < EFFECTLIST.getNumChildren(); i++) {
            auto e = EFFECTLIST.getChild(i);

            switch ((int) e[IDs::Number]) {
                case 0:
                    effectList.add(new NoEffect(e));
                    break;
                case 1:
                    effectList.add(new SumVolumeUp(e));
                    break;
                case 2:
                    effectList.add(new SumVolumeDown(e));
                    break;
                case 3:
                    effectList.add(new LeftSolo(e));
                    break;
                case 4:
                    effectList.add(new RightSolo(e));
                    break;
                case 5:
                    effectList.add(new Mono(e));
                    break;
                case 6:
                    effectList.add(new LRSwitched(e));
                    break;
                case 7:
                    effectList.add(new MidVolumeUp(e));
                    break;
                case 8:
                    effectList.add(new MidVolumeDown(e));
                    break;
                case 9:
                    effectList.add(new SideVolumeUp(e));
                    break;
                case 10:
                    effectList.add(new SideVolumeDown(e));
                    break;
                default:
                    DBG("Couldn't add effect");
                    break;
            }
        }
    }
    if (effectList.size() != (EFFECTLIST.getNumChildren()+1))
        DBG("you forgot an effect!");
    
    effectToPlay = effectList[0];
}

TransportManager::~TransportManager()
{
    TransportManager::instance = nullptr;
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
            setState(STARTING_ORIGINAL);
        }
        else {
            setState(STOPPING);
        }
    }
    
    else if (!ui.shouldPlayOriginal()) {
        if (getState() == TransportState::STOPPED) {
            setState(STARTING_EFFECT);
        }
        else {
            setState(TransportState::STOPPING);
        }
    }
}
