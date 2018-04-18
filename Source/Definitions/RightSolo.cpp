/*
  ==============================================================================
	RightSolo.cpp
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "RightSolo.h"

RightSolo::RightSolo () {}
RightSolo::~RightSolo () {}

void RightSolo::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
	float* const leftChannel = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);

	for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
	{
		leftChannel[sample] = 0;
	}
}