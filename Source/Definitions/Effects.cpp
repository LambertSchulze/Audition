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
Effect::Effect (String n, String t) : name(n), type(t) {}
Effect::~Effect() {}

void Effect::process        (const AudioSourceChannelInfo& bufferToFill) {Effect::processEffect   (bufferToFill);}
void Effect::processEffect  (const AudioSourceChannelInfo& bufferToFill) {}

String Effect::getName      () const        { return this->name; }
String Effect::getType      () const        { return type; }
void Effect::setLevel       (float level)   { this->level = level; }
float Effect::getLevel      () const        { return level; }

//==============================================================================
NoEffect::NoEffect () : Effect("No Effect", "Special") {}
NoEffect::~NoEffect () {}

void NoEffect::processEffect (const AudioSourceChannelInfo& bufferToFill) {}

//==============================================================================
LeftSolo::LeftSolo () : Effect("Left Solo", "Stereo Image") {}
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
RightSolo::RightSolo () : Effect("Right Solo", "Stereo Image") {}
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
Mono::Mono () : Effect("Mono", "Stereo Image")	{reduction = 0.5;}
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
LRSwitched::LRSwitched () : Effect("LR Switched", "Stereo Image") {}
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
SumVolumeUp::SumVolumeUp  () : Effect("Sum Volume Up", "Loudness") {gain = 2;}
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
SumVolumeDown::SumVolumeDown  () : Effect("Sum Volume Down", "Loudness") {gain = 0.5;}
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
MidVolumeUp::MidVolumeUp  () : Effect("Mid Volume Up", "Stereo Image") {gain = 2;}
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
MidVolumeDown::MidVolumeDown  () : Effect("Mid Volume Down", "Stereo Image") {gain = 0.5;}
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
SideVolumeUp::SideVolumeUp  () : Effect("Side Volume Up", "Stereo Image") {gain = 2;}
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
SideVolumeDown::SideVolumeDown  () : Effect("Side Volume Down", "Stereo Image") {gain = 0.5;}
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
Filter::Filter  (AudioSource* as) : Effect("Filter", "Colour"), parentSource(as),
    iirFilter(parentSource, false)
{}
Filter::~Filter () {}

void Filter::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    
}
