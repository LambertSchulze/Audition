/*
  ==============================================================================
	LeftSolo.cpp
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LeftSolo.h"

LeftSolo::LeftSolo () {}
LeftSolo::~LeftSolo () {}

void LeftSolo::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
	float* const rightChannel = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);

	for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
	{
		rightChannel[sample] = 0;
	}
}
