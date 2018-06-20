/*
 ==============================================================================
 
 Effect.cpp
 Created: 8 Mar 2018 8:31:48pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "Effects.h"
#include "../Definitions/Definitions.h"

//==============================================================================
Effect::Effect (ValueTree& v)
    : state(v)
{
    jassert(state.hasType(IDs::Effect));
    name.referTo(state, IDs::EffectName, nullptr);
    type.referTo(state, IDs::EffectType, nullptr);
    level.referTo(state, IDs::Level, nullptr);
    velocity.referTo(state, IDs::Velocity, nullptr);
}

Effect::~Effect()
{}

void Effect::process (const AudioSourceChannelInfo& bufferToFill)
{
    Effect::processEffect (bufferToFill);
}

void Effect::processEffect (const AudioSourceChannelInfo& bufferToFill)
{}

//==============================================================================
NoEffect::NoEffect (ValueTree& v)
    : Effect(v)
{}

NoEffect::~NoEffect ()
{}

void NoEffect::processEffect (const AudioSourceChannelInfo& bufferToFill)
{}

String NoEffect::getDetailedName()
{
    return "No Effect";
}

//==============================================================================
LeftSolo::LeftSolo (ValueTree& v)
    : Effect(v)
{}

LeftSolo::~LeftSolo ()
{}

void LeftSolo::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
	float* const rightChannel = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);

	for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
	{
		rightChannel[sample] = 0;
	}
}

String LeftSolo::getDetailedName()
{
    return "Left Channel Solo";
}

//==============================================================================
RightSolo::RightSolo (ValueTree& v)
    : Effect(v)
{}

RightSolo::~RightSolo ()
{}

void RightSolo::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
	float* const leftChannel = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);

	for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
	{
		leftChannel[sample] = 0;
	}
}

String RightSolo::getDetailedName()
{
    return "Right Channel Solo";
}

//==============================================================================
Mono::Mono (ValueTree& v)
    : Effect(v)
{}

Mono::~Mono ()
{}

void Mono::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
	float* const leftChannel 	= bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
	float* const rightChannel 	= bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);

	for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
	{
		const float f 			= leftChannel[sample];
		leftChannel[sample] 	+= rightChannel[sample];
		rightChannel[sample] 	+= f;
        
        leftChannel[sample]     = leftChannel[sample] * 0.5;
        rightChannel[sample]    = rightChannel[sample] * 0.5;
	}
}

String Mono::getDetailedName()
{
    return "Mono";
}

//==============================================================================
LRSwitched::LRSwitched (ValueTree& v)
    : Effect(v)
{}

LRSwitched::~LRSwitched()
{}

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

String LRSwitched::getDetailedName()
{
    return "Left and Right Channel switched";
}

//==============================================================================
SumVolumeUp::SumVolumeUp  (ValueTree& v)
    : Effect(v)
{}

SumVolumeUp::~SumVolumeUp ()
{}

void SumVolumeUp::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    float gain = Decibels::decibelsToGain(levelToDB());
    
	for (int channel = 0; channel < 2; ++channel)
	{
		float* const buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

		for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
		{
			buffer[sample] = buffer[sample] * gain;
		}
	}
}

float SumVolumeUp::levelToDB()
{
    if (1 <= level && level < 10) // 3dB
        return 3.0;
    else if (10 <= level && level < 20) // 2dB
        return 2.0;
    else if (20 <= level && level < 50) // 1,5 dB
        return 1.5;
    else if (50 <= level && level < 80) // 1 dB
        return 1.0;
    else if (80 <= level && level < 85) // 0,5 dB
        return 0.5;
    else if (85 <= level && level < 90) // 0,4 dB
        return 0.4;
    else if (90 <= level && level < 95) // 0,3 dB
        return 0.3;
    else if (95 <= level && level < 100) // 0,2 dB
        return 0.2;
    else if (level == 100) // 0,1 dB
        return 0.1;
    else // incorrect level
        return 0;
}

String SumVolumeUp::getDetailedName()
{
    String output = "Sum +" + String(levelToDB()) + " dB";
    return output;
}

//==============================================================================
SumVolumeDown::SumVolumeDown (ValueTree& v)
    : Effect(v)
{}

SumVolumeDown::~SumVolumeDown ()
{}

void SumVolumeDown::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    float gain = Decibels::decibelsToGain(levelToDB());
    
	for (int channel = 0; channel < 2; ++channel)
	{
		float* const buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

		for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
		{
			buffer[sample] = buffer[sample] * gain;
		}
	}
}

float SumVolumeDown::levelToDB()
{
    if (1 <= level && level < 10) // -3dB
        return -3.0;
    else if (10 <= level && level < 20) // -2dB
        return -2.0;
    else if (20 <= level && level < 50) // -1,5 dB
        return -1.5;
    else if (50 <= level && level < 80) // -1 dB
        return -1.0;
    else if (80 <= level && level < 85) // -0,5 dB
        return -0.5;
    else if (85 <= level && level < 90) // -0,4 dB
        return -0.4;
    else if (90 <= level && level < 95) // -0,3 dB
        return -0.3;
    else if (95 <= level && level < 100) // -0,2 dB
        return -0.2;
    else if (level == 100) // -0,1 dB
        return -0.1;
    else // incorrect level
        return 0;
}

String SumVolumeDown::getDetailedName()
{
    String output = "Sum " + String(levelToDB()) + " dB";
    return output;
}

//==============================================================================
MidVolumeUp::MidVolumeUp (ValueTree& v)
    : Effect(v)
{}

MidVolumeUp::~MidVolumeUp ()
{}

void MidVolumeUp::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    float gain = Decibels::decibelsToGain(levelToDB());
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

float MidVolumeUp::levelToDB()
{
    if (1 <= level && level < 10) // 3dB
        return 3.0;
    else if (10 <= level && level < 20) // 2dB
        return 2.0;
    else if (20 <= level && level < 50) // 1,5 dB
        return 1.5;
    else if (50 <= level && level < 80) // 1 dB
        return 1.0;
    else if (80 <= level && level < 85) // 0,5 dB
        return 0.5;
    else if (85 <= level && level < 90) // 0,4 dB
        return 0.4;
    else if (90 <= level && level < 95) // 0,3 dB
        return 0.3;
    else if (95 <= level && level < 100) // 0,2 dB
        return 0.2;
    else if (level == 100) // 0,1 dB
        return 0.1;
    else // incorrect level
        return 0;
}

String MidVolumeUp::getDetailedName()
{
    String output = "Mid Channel +" + String(levelToDB()) + " dB";
    return output;
}

//==============================================================================
MidVolumeDown::MidVolumeDown (ValueTree& v)
    : Effect(v)
{}

MidVolumeDown::~MidVolumeDown () {}

void MidVolumeDown::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    float gain = Decibels::decibelsToGain(levelToDB());
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

float MidVolumeDown::levelToDB()
{
    if (1 <= level && level < 10) // -3dB
        return -3.0;
    else if (10 <= level && level < 20) // -2dB
        return -2.0;
    else if (20 <= level && level < 50) // -1,5 dB
        return -1.5;
    else if (50 <= level && level < 80) // -1 dB
        return -1.0;
    else if (80 <= level && level < 85) // -0,5 dB
        return -0.5;
    else if (85 <= level && level < 90) // -0,4 dB
        return -0.4;
    else if (90 <= level && level < 95) // -0,3 dB
        return -0.3;
    else if (95 <= level && level < 100) // -0,2 dB
        return -0.2;
    else if (level == 100) // -0,1 dB
        return -0.1;
    else // incorrect level
        return 0;
}

String MidVolumeDown::getDetailedName()
{
    String output = "Mid Channel " + String(levelToDB()) + " dB";
    return output;
}

//==============================================================================
SideVolumeUp::SideVolumeUp (ValueTree& v)
    : Effect(v)
{}

SideVolumeUp::~SideVolumeUp ()
{}

void SideVolumeUp::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    float gain = levelToDB();
    const float sqrt2 = MathConstants<float>::sqrt2;
    
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

float SideVolumeUp::levelToDB()
{
    if (1 <= level && level < 10) // 3dB
        return 3.0;
    else if (10 <= level && level < 20) // 2dB
        return 2.0;
    else if (20 <= level && level < 50) // 1,5 dB
        return 1.5;
    else if (50 <= level && level < 80) // 1 dB
        return 1.0;
    else if (80 <= level && level < 85) // 0,5 dB
        return 0.5;
    else if (85 <= level && level < 90) // 0,4 dB
        return 0.4;
    else if (90 <= level && level < 95) // 0,3 dB
        return 0.3;
    else if (95 <= level && level < 100) // 0,2 dB
        return 0.2;
    else if (level == 100) // 0,1 dB
        return 0.1;
    else // incorrect level
        return 0;
}

String SideVolumeUp::getDetailedName()
{
    String output = "Side Channel +" + String(levelToDB()) + " dB";
    return output;
}

//==============================================================================
SideVolumeDown::SideVolumeDown (ValueTree& v)
    : Effect(v)
{}

SideVolumeDown::~SideVolumeDown ()
{}

void SideVolumeDown::processEffect (const AudioSourceChannelInfo& bufferToFill)
{
    float gain = levelToDB();
    const float sqrt2 = MathConstants<float>::sqrt2;
    
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

float SideVolumeDown::levelToDB()
{
    if (1 <= level && level < 10) // 3dB
        return -3.0;
    else if (10 <= level && level < 20) // 2dB
        return -2.0;
    else if (20 <= level && level < 50) // 1,5 dB
        return -1.5;
    else if (50 <= level && level < 80) // 1 dB
        return -1.0;
    else if (80 <= level && level < 85) // 0,5 dB
        return -0.5;
    else if (85 <= level && level < 90) // 0,4 dB
        return -0.4;
    else if (90 <= level && level < 95) // 0,3 dB
        return -0.3;
    else if (95 <= level && level < 100) // 0,2 dB
        return -0.2;
    else if (level == 100) // 0,1 dB
        return -0.1;
    else // incorrect level
        return 0;
}

String SideVolumeDown::getDetailedName()
{
    String output = "Side Channel " + String(levelToDB()) + " dB";
    return output;
}

//==============================================================================

