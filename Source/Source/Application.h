#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "UI/MainWindow.h"
#include "UI/AuditionLookAndFeel.h"
#include "StoredSettings.h"


class Application  : public JUCEApplication
{
    std::unique_ptr<MainWindow> ui;
    AuditionLookAndFeel lookAndFeel;
    
public:
    Application();
    
    static Application& getApp();
    //static ApplicationCommandManager& getCommandManager();
    
    //==============================================================================
    void initialise (const String& commandLine) override;
    void shutdown() override                                { ui = nullptr; }
    void systemRequestedQuit() override                     { quit(); }
    
    //==============================================================================
    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return false; }

    //==============================================================================
    PropertiesFile::Options getPropertyFileOptions ();

    //==============================================================================
    std::unique_ptr<StoredSettings> storedSettings;
};
