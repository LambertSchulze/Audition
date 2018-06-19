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
    Effect (String name, String type, int level, int velocity);
    virtual ~Effect();

    void process (const AudioSourceChannelInfo& bufferToFill);
    virtual void processEffect (const AudioSourceChannelInfo& bufferToFill);
    
    String getName () const;
    String getType () const;
    
    void levelUp ();
    void levelDown ();
    
    virtual String getDetailedName () =0;
    
protected:
    const String name; // Name of the effect
    const String type; // Category
    int level; // from 0 to 100
    int velocity; // from 1 to 4
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Effect)
};

//==============================================================================
class NoEffect : public Effect
{
public:
    NoEffect ();
	~NoEffect ();

	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class LeftSolo : public Effect
{
public:
	LeftSolo ();
	~LeftSolo ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class RightSolo : public Effect
{
public:
	RightSolo ();
	~RightSolo ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class Mono : public Effect
{
public:
	Mono ();
	~Mono ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class LRSwitched : public Effect
{
public:
    LRSwitched ();
    ~LRSwitched();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class SumVolumeUp : public Effect
{
public:
	SumVolumeUp  ();
	~SumVolumeUp ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
    float levelToDB();
};

//==============================================================================
class SumVolumeDown : public Effect
{
public:
	SumVolumeDown  ();
	~SumVolumeDown ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
    float levelToDB();

private:
    float gain;
};

//==============================================================================
class MidVolumeUp : public Effect
{
public:
    MidVolumeUp  ();
    ~MidVolumeUp ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
    float levelToDB();
    
private:
    float gain;
};

//==============================================================================
class MidVolumeDown : public Effect
{
public:
    MidVolumeDown  ();
    ~MidVolumeDown ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
    
private:
    float gain;
};

//==============================================================================
class SideVolumeUp : public Effect
{
public:
    SideVolumeUp  ();
    ~SideVolumeUp ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
    
private:
    float gain;
};

//==============================================================================
class SideVolumeDown : public Effect
{
public:
    SideVolumeDown  ();
    ~SideVolumeDown ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
    
private:
    float gain;
};

//==============================================================================
class Filter : public Effect
{
public:
    Filter  (AudioSource*);
    ~Filter ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
    
private:
    AudioSource* parentSource;
    IIRFilterAudioSource iirFilter;
    IIRCoefficients ic;
};
