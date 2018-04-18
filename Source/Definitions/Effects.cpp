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

void Effect::process        (const AudioSourceChannelInfo& bufferToFill)
{
    Effect::processEffect   (bufferToFill);
}

void Effect::processEffect  (const AudioSourceChannelInfo& bufferToFill) {}

void Effect::setName        (String name)   { this->name = name; }
String Effect::getName      ()              { return this->name; }
String Effect::getType      ()              { return type; }

void Effect::setLevel       (float level)   { this->level = level; }
float Effect::getLevel      ()              { return level; }
