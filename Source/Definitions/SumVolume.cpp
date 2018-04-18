/*
  ==============================================================================
	SumVolume.cpp
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SumVolume.h"

SumVolume::SumVolume ()
{
    reduction = Decibels::decibelsToGain(-2);
}

SumVolume::~SumVolume () {}

void SumVolume::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
	for (int channel = 0; channel < 2; ++channel)
	{
		float* const buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

		for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
		{
			buffer[sample] = buffer[sample] * level;
		}
	}
}