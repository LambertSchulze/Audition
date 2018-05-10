/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Gui/AuditionLookAndFeel.cpp"

Component* createMainContentComponent();

//==============================================================================
class NewProjectApplication  : public JUCEApplication
{
public:
    //==============================================================================
    NewProjectApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        mainWindow = new MainWindow (getApplicationName());
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {}

    //==============================================================================
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name, Colours::white, DocumentWindow::allButtons)
        {
            AuditionLookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
            
            setUsingNativeTitleBar (true);
            setContentOwned (createMainContentComponent(), true);
            setResizable (true, true);

            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        AuditionLookAndFeel lookAndFeel;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
START_JUCE_APPLICATION (NewProjectApplication)
