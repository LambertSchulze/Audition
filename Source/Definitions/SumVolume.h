/*
  ==============================================================================
	SumVolume.h
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Effect.h"

class SumVolume : public Effect
{
public:
	SumVolume ();
	~SumVolume ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill);

private:
	String type {"Volume"};
    String name {"SumVolume"};
    
    float reduction;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SumVolume)
};