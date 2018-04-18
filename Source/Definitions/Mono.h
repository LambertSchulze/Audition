/*
  ==============================================================================
	Mono.h
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Effect.h"

class Mono : public Effect
{
public:
	Mono ();
	~Mono ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;

private:
	String type {"StereoImage"};
    String name {"Mono"};
    
    float reduction;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mono)
};