/*
==============================================================================

DataHandler.h
Created: 3 May 2018 9:18:38pm
Author:  Lambert Schulze

==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class DataHandler
{
public:
    DataHandler();
    ~DataHandler();

    ValueTree& getValueTree();

private:
    void loadData(File);
    void saveData(File);

    void setupProperties();

    File saveFile;
    ValueTree vt;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataHandler)
};
