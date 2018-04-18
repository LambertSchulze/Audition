/*
  ==============================================================================
	Mono.cpp
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Mono.h"

Mono::Mono ()
{
    reduction = Decibels::decibelsToGain(-2);
}

Mono::~Mono () {}

void Mono::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
	float* const leftChannel 	= bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
	float* const rightChannel 	= bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);

	for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
	{
		const float f 			= leftChannel[sample];
		leftChannel[sample] 	+= rightChannel[sample];
		rightChannel[sample] 	+= f;
        
        leftChannel[sample]     = leftChannel[sample] * reduction;
        rightChannel[sample]    = rightChannel[sample] * reduction;
	}
}