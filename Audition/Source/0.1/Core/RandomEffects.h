/*
 ==============================================================================
 
 RandomEffects.h
 Created: 23 May 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class RandomEffects
{
public:
    RandomEffects(ValueTree& tree) : vt(tree)   {};
    ~RandomEffects()                            {};

    void newQuickQuiz();
    
private:
    ValueTree vt;
    Random r;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RandomEffects)
};
