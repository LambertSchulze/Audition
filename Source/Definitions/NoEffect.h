/*
  ==============================================================================
	NoEffect.h
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Effect.h"

class NoEffect : public Effect
{
public:
	NoEffect ();
	~NoEffect ();

	void processEffect (const AudioSourceChannelInfo& bufferToFill) override;

private:
	String type {"Other"};
    String name {"NoEffect"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoEffect)
};