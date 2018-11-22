#include "MainWindow.h"
#include "MainComponent.h"
#include "../Application.h"
#include "../SavedFiles.h"


static const int MIN_WINDOW_WIDTH = 600;
static const int MIN_WINDOW_HEIGHT = 400;


MainWindow::MainWindow (String applicationName)
: DocumentWindow (applicationName,
                  LookAndFeel::getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId),
                  DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (false);
    setContentOwned (new MainComponent(), true);
    setResizable (true, false);
    setResizeLimits(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT, 99999999, 99999999);
    setDropShadowEnabled (true);
    
    auto* savedFiles = Application::getApp().savedFiles.get();
    
    if (savedFiles->getWindowState() == "")
        centreWithSize(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT);
    else
        restoreWindowStateFromString(savedFiles->getWindowState());
    
    setFullScreen(savedFiles->getFullscreenState());
    
    setVisible (true);
}

MainWindow::~MainWindow()
{
    auto* savedFiles = Application::getApp().savedFiles.get();
    
    savedFiles->setWindowState(getWindowStateAsString());
    savedFiles->setFullscreenState(isFullScreen());
}

void MainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
