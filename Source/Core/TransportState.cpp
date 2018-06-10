/*
 ==============================================================================
 
 TransportState.cpp
 Created: 10 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "TransportState.h"

TransportState::State TransportState::state = State::STOPPED;

int TransportState::playbackEffect = 0;

int TransportState::startTime = 0;

String TransportState::playbackFile = "";
