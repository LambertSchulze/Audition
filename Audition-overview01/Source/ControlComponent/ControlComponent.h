/*
 ==============================================================================
 
 ControlComponent.h
 Created: 18 Mar 2018 9:19:01pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "SourceComponent.h"
#include "TransportControl.h"

//==============================================================================
/*
 */
class ControlComponent    : public Component
{
public:
    ControlComponent(ValueTree&);
    ~ControlComponent();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    ValueTree tree;
    
    SourceComponent sourceComponent;
    TransportControl transportControl;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlComponent)
};
