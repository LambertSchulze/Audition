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

//==============================================================================
Mono::Mono ()	{reduction = Decibels::decibelsToGain(-2);}
Mono::~Mono () 	{}

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

//==============================================================================
LRSwitched::LRSwitched () {}
LRSwitched::~LRSwitched() {}

void LRSwitched::processEffect(const AudioSourceChannelInfo& bufferToFill)
{
    float* const leftChannel    = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    float* const rightChannel   = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
    
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        const float f           = leftChannel[sample];
        leftChannel[sample]     = rightChannel[sample];
        rightChannel[sample]    = f;
    }
}

//==============================================================================
SumVolumeUp::SumVolumeUp  () {gain = Decibels::decibelsToGain(+2);}
SumVolumeUp::~SumVolumeUp () {}

void SumVolumeUp::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
	for (int channel = 0; channel < 2; ++channel)
	{
		float* const buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

		for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
		{
			buffer[sample] = buffer[sample] * gain;
		}
	}
}

//==============================================================================
SumVolumeDown::SumVolumeDown  () {gain = Decibels::decibelsToGain(-2);}
SumVolumeDown::~SumVolumeDown () {}

void SumVolumeDown::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
	for (int channel = 0; channel < 2; ++channel)
	{
		float* const buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

		for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
		{
			buffer[sample] = buffer[sample] * gain;
		}
	}
}

//==============================================================================
MidVolumeUp::MidVolumeUp  () {gain = Decibels::decibelsToGain(+2);}
MidVolumeUp::~MidVolumeUp () {}

void MidVolumeUp::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    const float reduction       = Decibels::decibelsToGain(-2);
    
    float* const leftChannel    = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    float* const rightChannel   = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
    
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float midChannel        = leftChannel[sample] + rightChannel[sample];
        float sideChannel       = leftChannel[sample] - rightChannel[sample];
        
        midChannel              = midChannel * gain;
        
        leftChannel[sample]     = (midChannel + sideChannel) * reduction;
        rightChannel[sample]    = (midChannel - sideChannel) * reduction;
    }
}

//==============================================================================
MidVolumeDown::MidVolumeDown  () {gain = Decibels::decibelsToGain(-2);}
MidVolumeDown::~MidVolumeDown () {}

void MidVolumeDown::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    const float reduction       = Decibels::decibelsToGain(-2);
    
    float* const leftChannel    = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    float* const rightChannel   = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
    
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float midChannel        = leftChannel[sample] + rightChannel[sample];
        float sideChannel       = leftChannel[sample] - rightChannel[sample];
        
        midChannel              = midChannel * gain;
        
        leftChannel[sample]     = (midChannel + sideChannel) * reduction;
        rightChannel[sample]    = (midChannel - sideChannel) * reduction;
    }
}

//==============================================================================
SideVolumeUp::SideVolumeUp  () {gain = Decibels::decibelsToGain(+2);}
SideVolumeUp::~SideVolumeUp () {}

void SideVolumeUp::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    const float reduction       = Decibels::decibelsToGain(-2);
    
    float* const leftChannel    = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    float* const rightChannel   = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
    
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float midChannel        = leftChannel[sample] + rightChannel[sample];
        float sideChannel       = leftChannel[sample] - rightChannel[sample];
        
        sideChannel              = midChannel * gain;
        
        leftChannel[sample]     = (midChannel + sideChannel) * reduction;
        rightChannel[sample]    = (midChannel - sideChannel) * reduction;
    }
}

//==============================================================================
SideVolumeDown::SideVolumeDown  () {gain = Decibels::decibelsToGain(-2);}
SideVolumeDown::~SideVolumeDown () {}

void SideVolumeDown::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    const float reduction       = Decibels::decibelsToGain(-2);
    
    float* const leftChannel    = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    float* const rightChannel   = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
    
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float midChannel        = leftChannel[sample] + rightChannel[sample];
        float sideChannel       = leftChannel[sample] - rightChannel[sample];
        
        sideChannel              = midChannel * gain;
        
        leftChannel[sample]     = (midChannel + sideChannel) * reduction;
        rightChannel[sample]    = (midChannel - sideChannel) * reduction;
    }
}