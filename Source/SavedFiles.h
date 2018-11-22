#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class SavedFiles
{
    PropertiesFile windowProperties;
    
public:
    SavedFiles();
    ~SavedFiles();

    String getWindowState();
    bool getFullscreenState();
    
    void setWindowState(String windowState);
    void setFullscreenState(bool isFullscreen);
};
