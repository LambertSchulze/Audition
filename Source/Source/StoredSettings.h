#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class StoredSettings
{
    PropertiesFile windowProperties;
    
public:
    StoredSettings();
    ~StoredSettings();

    String getWindotState();
};
