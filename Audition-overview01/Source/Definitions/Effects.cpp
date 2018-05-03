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
Mono::Mono ()	{reduction = 0.5;}
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
SumVolumeUp::SumVolumeUp  () {gain = 2;}
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
SumVolumeDown::SumVolumeDown  () {gain = 0.5;}
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
MidVolumeUp::MidVolumeUp  () {gain = 2;}
MidVolumeUp::~MidVolumeUp () {}

void MidVolumeUp::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    const float sqrt2           = 1.4142135623730950488;
    
    float* const leftChannel    = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    float* const rightChannel   = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
    
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float midChannel        = (leftChannel[sample] + rightChannel[sample]) / sqrt2;
        float sideChannel       = (leftChannel[sample] - rightChannel[sample]) / sqrt2;
        
        midChannel              = midChannel * gain;
        
        leftChannel[sample]     = midChannel + sideChannel;
        rightChannel[sample]    = midChannel - sideChannel;
    }
}

//==============================================================================
MidVolumeDown::MidVolumeDown  () {gain = 0.5;}
MidVolumeDown::~MidVolumeDown () {}

void MidVolumeDown::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    const float sqrt2           = 1.4142135623730950488;
    
    float* const leftChannel    = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    float* const rightChannel   = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
    
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float midChannel        = (leftChannel[sample] + rightChannel[sample]) / sqrt2;
        float sideChannel       = (leftChannel[sample] - rightChannel[sample]) / sqrt2;
        
        midChannel              = midChannel * gain;
        
        leftChannel[sample]     = midChannel + sideChannel;
        rightChannel[sample]    = midChannel - sideChannel;
    }
}

//==============================================================================
SideVolumeUp::SideVolumeUp  () {gain = 2;}
SideVolumeUp::~SideVolumeUp () {}

void SideVolumeUp::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    const float sqrt2           = 1.4142135623730950488;
    
    float* const leftChannel    = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    float* const rightChannel   = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
    
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float midChannel        = (leftChannel[sample] + rightChannel[sample]) / sqrt2;
        float sideChannel       = (leftChannel[sample] - rightChannel[sample]) / sqrt2;
        
        sideChannel              = sideChannel * gain;
        
        leftChannel[sample]     = midChannel + sideChannel;
        rightChannel[sample]    = midChannel - sideChannel;
    }
}

//==============================================================================
SideVolumeDown::SideVolumeDown  () {gain = 0.5;}
SideVolumeDown::~SideVolumeDown () {}

void SideVolumeDown::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    const float sqrt2           = 1.4142135623730950488;
    
    float* const leftChannel    = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    float* const rightChannel   = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
    
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float midChannel        = (leftChannel[sample] + rightChannel[sample]) / sqrt2;
        float sideChannel       = (leftChannel[sample] - rightChannel[sample]) / sqrt2;
        
        sideChannel              = sideChannel * gain;
        
        leftChannel[sample]     = midChannel + sideChannel;
        rightChannel[sample]    = midChannel - sideChannel;
    }
}

//==============================================================================
Filter::Filter  (AudioSource* as)
:   parentSource(as),
    iirFilter(parentSource, false)
{}
Filter::~Filter () {}

void Filter::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    
}