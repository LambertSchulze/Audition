/*
  ==============================================================================

    Effect.h
    Created: 5 Mar 2018 9:42:47pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
class Effect
{
public:
    Effect ();
//    Effect (String, String);
//    Effect (String, String, float);
    virtual ~Effect();
    void process (const AudioSourceChannelInfo& bufferToFill);
    
    virtual void processEffect  (const AudioSourceChannelInfo& bufferToFill);
    
    void setName                (String name);
    String getName              ();
    String getType              ();
    
    void setLevel               (float level);
    float getLevel              ();
    
protected:
    String name;
    String type;
    float level;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Effect)
};