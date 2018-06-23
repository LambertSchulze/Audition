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

	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class LeftSolo : public Effect
{
public:
	LeftSolo (ValueTree& v);
	~LeftSolo ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class RightSolo : public Effect
{
public:
	RightSolo (ValueTree& v);
	~RightSolo ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class Mono : public Effect
{
public:
	Mono (ValueTree& v);
	~Mono ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class LRSwitched : public Effect
{
public:
    LRSwitched (ValueTree& v);
    ~LRSwitched();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    String getDetailedName () override;
};

//==============================================================================
class SumVolumeUp : public Effect
{
public:
	SumVolumeUp  (ValueTree& v);
	~SumVolumeUp ();
	
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
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    float levelToDB();
    String getDetailedName() override;
};

//==============================================================================
class HpFilter : public Effect
{
public:
    HpFilter  (ValueTree& v);
    ~HpFilter ();
    
    void processEffect (const AudioSourceChannelInfo& bufferToFill) override;
    
    float levelToHz();
    String getDetailedName() override;
    
private:
    ScopedPointer<IIRFilter> filterLeft;
    ScopedPointer<IIRFilter> filterRight;
    
    int oldLevel;
};
