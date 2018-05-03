/*
==============================================================================

DataHandler.h
Created: 3 May 2018 9:18:38pm
Author:  Lambert Schulze

==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*A class for setting up the ValueTree Object and some lobal functions to access
the different nodes.*/

const ValueTree& getNode(const Identifier);


class DataHandler
{
public:
    DataHandler();
    ~DataHandler();

    const ValueTree& getValueTree();

private:
    void loadData();
    void saveData();

    void setupValueTree();

    const File saveFile;
    ValueTree vt;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataHandler)
};
