/*
  ==============================================================================
	LeftSolo.h
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Effect.h"

class LeftSolo : public Effect
{
public:
	LeftSolo ();
	~LeftSolo ();
	
	void processEffect (const AudioSourceChannelInfo& bufferToFill);

private:
	String type {"Solo"};
    String name {"LeftSolo"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeftSolo)
};