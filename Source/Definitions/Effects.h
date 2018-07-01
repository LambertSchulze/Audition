/*
  ==============================================================================

    Effects.h
    Created: 5 Mar 2018 9:42:47pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class Effect
{
public:
    Effect (ValueTree& effectState);
    virtual ~Effect();

    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) =0;
    
    void process (const AudioSourceChannelInfo& bufferToFill);
    virtual void processEffect (const AudioSourceChannelInfo& bufferToFill);
    
    virtual String getDetailedName () =0;
    
protected:
    ValueTree state;
    CachedValue<String> name;
    CachedValue<String> type;
    CachedValue<int> level;
    CachedValue<int> velocity;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Effect)
};

//==============================================================================
class NoEffect : public Effect
{
public:
    NoEffect (ValueTree& v);
	~NoEffect ();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class LeftSolo : public Effect
{
public:
	LeftSolo (ValueTree& v);
	~LeftSolo ();
	
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class RightSolo : public Effect
{
public:
	RightSolo (ValueTree& v);
	~RightSolo ();
	
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class Mono : public Effect
{
public:
	Mono (ValueTree& v);
	~Mono ();
	
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class LRSwitched : public Effect
{
public:
    LRSwitched (ValueTree& v);
    ~LRSwitched();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class PhaseInverted : public Effect
{
public:
    PhaseInverted (ValueTree& v);
    ~PhaseInverted();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class SumVolumeUp : public Effect
{
public:
	SumVolumeUp  (ValueTree& v);
	~SumVolumeUp ();
	
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    float levelToDB();
    String getDetailedName () override;
};

//==============================================================================
class SumVolumeDown : public Effect
{
public:
	SumVolumeDown  (ValueTree& v);
	~SumVolumeDown ();
	
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    float levelToDB();
    String getDetailedName () override;
};

//==============================================================================
class MidVolumeUp : public Effect
{
public:
    MidVolumeUp  (ValueTree& v);
    ~MidVolumeUp ();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    float levelToDB();
    String getDetailedName () override;
};

//==============================================================================
class MidVolumeDown : public Effect
{
public:
    MidVolumeDown  (ValueTree& v);
    ~MidVolumeDown ();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    float levelToDB();
    String getDetailedName() override;
};

//==============================================================================
class SideVolumeUp : public Effect
{
public:
    SideVolumeUp  (ValueTree& v);
    ~SideVolumeUp ();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    float levelToDB();
    String getDetailedName() override;
};

//==============================================================================
class SideVolumeDown : public Effect
{
public:
    SideVolumeDown  (ValueTree& v);
    ~SideVolumeDown ();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    float levelToDB();
    String getDetailedName() override;
};

//==============================================================================
class HpFilter : public Effect      // Filter effect with IIRFilter class
{
public:
    HpFilter  (ValueTree& v);
    ~HpFilter ();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {};
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    float levelToHz();
    String getDetailedName() override;
    
private:
    ScopedPointer<IIRFilter> filterLeft;
    ScopedPointer<IIRFilter> filterRight;
    
    int oldLevel;
};

//==============================================================================
class LPFilter : public Effect      // Filter effect with IIRFilterAudioSource class
{
public:
    LPFilter    (ValueTree& v, AudioSource* a);
    ~LPFilter   ();
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    float levelToHz();
    String getDetailedName() override;
    
private:
    IIRFilterAudioSource filter;
};
