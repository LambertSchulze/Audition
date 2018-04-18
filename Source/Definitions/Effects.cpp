/*
 ==============================================================================
 
 Effect.cpp
 Created: 8 Mar 2018 8:31:48pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "Effects.h"

//==============================================================================
Effect::Effect () {}
Effect::~Effect() {}

void Effect::process        (const AudioSourceChannelInfo& bufferToFill) {Effect::processEffect   (bufferToFill);}
void Effect::processEffect  (const AudioSourceChannelInfo& bufferToFill) {}

void Effect::setName        (String name)   { this->name = name; }
String Effect::getName      ()              { return this->name; }
String Effect::getType      ()              { return type; }
void Effect::setLevel       (float level)   { this->level = level; }
float Effect::getLevel      ()              { return level; }

//==============================================================================
NoEffect::NoEffect ()  {}
NoEffect::~NoEffect () {}

void NoEffect::processEffect (const AudioSourceChannelInfo& bufferToFill) {}

//==============================================================================
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

//==============================================================================
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
