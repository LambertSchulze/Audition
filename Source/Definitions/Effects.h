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
/*
 */
class Effect
{
public:
    Effect (String name, String type);
    virtual ~Effect();

    void process (const AudioSourceChannelInfo& bufferToFill);
    
    virtual void processEffect  (const AudioSourceChannelInfo& bufferToFill);
    
    String getName              () const;
    String getType              () const;
    
    void setLevel               (float level);
    float getLevel              () const;
    
protected:
    const String name;
    const String type;
    float level;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Effect)
};

//==============================================================================
class NoEffect : public Effect
{
public:
    NoEffect ();
	~NoEffect ();

	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoEffect)
};

//==============================================================================
class LeftSolo : public Effect
{
public:
	LeftSolo ();
	~LeftSolo ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill);

private:
	String type {"Solo"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeftSolo)
};

//==============================================================================
class RightSolo : public Effect
{
public:
	RightSolo ();
	~RightSolo ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill);

private:
	String type {"Solo"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RightSolo)
};

//==============================================================================
class Mono : public Effect
{
public:
	Mono ();
	~Mono ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;

private:
	String type {"StereoImage"};
    
    float reduction;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mono)
};

//==============================================================================
class LRSwitched : public Effect
{
public:
    LRSwitched ();
    ~LRSwitched();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
private:
    String type {"StereoImage"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LRSwitched)
};

//==============================================================================
class SumVolumeUp : public Effect
{
public:
	SumVolumeUp  ();
	~SumVolumeUp ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill);

private:
    String type {"Volume"};
    
    float gain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SumVolumeUp)
};

//==============================================================================
class SumVolumeDown : public Effect
{
public:
	SumVolumeDown  ();
	~SumVolumeDown ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill);

private:
    String type {"Volume"};
    
    float gain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SumVolumeDown)
};

//==============================================================================
class MidVolumeUp : public Effect
{
public:
    MidVolumeUp  ();
    ~MidVolumeUp ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill);
    
private:
    String type {"Volume"};
    
    float gain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidVolumeUp)
};

//==============================================================================
class MidVolumeDown : public Effect
{
public:
    MidVolumeDown  ();
    ~MidVolumeDown ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill);
    
private:
    String type {"Volume"};
    
    float gain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidVolumeDown)
};

//==============================================================================
class SideVolumeUp : public Effect
{
public:
    SideVolumeUp  ();
    ~SideVolumeUp ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill);
    
private:
    String type {"Volume"};
    
    float gain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SideVolumeUp)
};

//==============================================================================
class SideVolumeDown : public Effect
{
public:
    SideVolumeDown  ();
    ~SideVolumeDown ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill);
    
private:
    String type {"Volume"};
    
    float gain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SideVolumeDown)
};

//==============================================================================
class Filter : public Effect
{
public:
    Filter  (AudioSource*);
    ~Filter ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill);
    
private:
    String type {"Filter"};
    
    AudioSource* parentSource;
    IIRFilterAudioSource iirFilter;
    IIRCoefficients ic;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};
