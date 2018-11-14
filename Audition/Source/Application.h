/*
  ==============================================================================

    AuditionApplication.h
    Created: 2 Nov 2018 12:06:55pm
    Author:  Lambert Schulze

  ==============================================================================
*/
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"

class Application : public JUCEApplication
{
    std::unique_ptr<MainWindow> mainWindow;
    
public:
    Application();
    ~Application();

    //==============================================================================
    const String getApplicationName() override      { return "Audition"; }
    const String getApplicationVersion() override   { return ProjectInfo::versionString; }
    
    void initialise (const String& commandLine) override;
    bool moreThanOneInstanceAllowed() override      { return false; }
    void shutdown() override                        { mainWindow = nullptr; }
    void systemRequestedQuit() override             { quit(); }
};

START_JUCE_APPLICATION (Application)
