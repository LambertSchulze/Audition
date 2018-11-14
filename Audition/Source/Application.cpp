#include "Application.h"


Application::Application()      { DBG("constructing Application"); }

Application::~Application()     { DBG("deconstructing Application"); }

void Application::initialise(const juce::String &commandLine)
{
    mainWindow.reset(new MainWindow());
}
