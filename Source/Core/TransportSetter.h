/*
 ==============================================================================
 
 TransportSetter.h
 Created: 10 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TransportState.h"

class TransportSetter : public TransportState
{
public:
    TransportSetter() {};
    ~TransportSetter() {};
    
    void stateChanged() override {};
    void effectChanged() override {};
};
