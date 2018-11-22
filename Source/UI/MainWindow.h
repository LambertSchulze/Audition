#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class MainWindow :  public DocumentWindow
{
public:
    MainWindow (String applicationName);
    ~MainWindow();
    
    void closeButtonPressed();
};
