/*
  ==============================================================================
	RightSolo.h
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Effect.h"

class RightSolo : public Effect
{
public:
	RightSolo ();
	~RightSolo ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill);

private:
	String type {"Solo"};
    String name {"RightSolo"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RightSolo)
};