/*
 ==============================================================================
 
 TransportComponentLookAndFeel.h
 Created: 14 May 2018 8:51:56pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "AuditionLookAndFeel.h"

class TransportComponentLookAndFeel :    public LookAndFeel_V4
{
public:
    TransportComponentLookAndFeel ()
    {
        
    };
    
    ~TransportComponentLookAndFeel () {};
    
    AuditionLookAndFeel laf;
};
