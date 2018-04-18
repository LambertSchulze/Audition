/*
 ==============================================================================
 
 AudioComponent.h
 Created: 18 Mar 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "Definitions/Definitions.h"
#include "Definitions/AuditionLookAndFeel.cpp"
#include "Definitions/Effect.h"
#include "Definitions/NoEffect.h"
#include "Definitions/SumVolume.h"
#include "Definitions/LeftSolo.h"
#include "Definitions/RightSolo.h"
#include "Definitions/Mono.h"

#include "ControlComponent/ControlComponent.h"
#include "WindowContainer/WindowContainer.h"

//==============================================================================
/*
 */
class MainContentComponent   :  public AudioAppComponent,
                                public ValueTree::Listener,
                                public ChangeListener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();
    
    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    //==============================================================================
    void valueTreePropertyChanged (ValueTree&, const Identifier&) override;
    void valueTreeChildAdded (ValueTree&, ValueTree&) override;
    void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override;
    void valueTreeChildOrderChanged (ValueTree&, int, int) override;
    void valueTreeParentChanged (ValueTree&) override;
    void valueTreeRedirected (ValueTree&) override;
    
    //==============================================================================
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    //==============================================================================
    void setupProperties();
    void setReaderSource(String);
    
    void loadData();
    void saveData();
    
private:
    //==============================================================================
    ValueTree           mainVT;
    File                settingsFile;
    XmlElement*         fileDataXml;
    
    AudioFormatManager                      formatManager;
    ScopedPointer<AudioFormatReaderSource>  readerSource;
    AudioTransportSource                    transportSource;
    
    OwnedArray<Effect>  effectList;
    Effect*             currentEffect;
    bool                shouldProcessEffect;
    
    //==============================================================================
    ScopedPointer<ControlComponent> controlComponent;
    ScopedPointer<WindowContainer>  windowContainer;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }
