#include "MainWindow.h"
#include "MainComponent.h"

MainWindow::MainWindow (String applicationName)
: DocumentWindow (applicationName,
                  Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId),
                  DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (false);
    setContentOwned (new MainComponent(), true);
    
    setResizable (true, false);
    setDropShadowEnabled (true);
    if (!restoreWindowStateFromString(Application::getApp().storedSettings))
    centreWithSize (600, 400);
    
    setVisible (true);
}

MainWindow::~MainWindow()
{}

void MainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
