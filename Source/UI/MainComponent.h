#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class MainComponent :  public Component
{
public:
    MainComponent();
    ~MainComponent();
    
    void paint (Graphics& g);
    void resized();
};
