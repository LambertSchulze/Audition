#include "Application.h"


Application::Application()
{}

Application& Application::getApp()
{
    Application* const app = dynamic_cast<Application*>(JUCEApplication::getInstance());
    return *app;
}

void Application::initialise (const String& commandLine)
{
    savedFiles.reset (new SavedFiles());
    
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    ui.reset (new MainWindow(getApplicationName()));
}

PropertiesFile::Options Application::getPropertyFileOptions()
{
    PropertiesFile::Options options;
    options.applicationName = getApplicationName();
    options.filenameSuffix = ".settings";
    options.folderName = getApplicationName();
    options.osxLibrarySubFolder = "Application Support";
    options.commonToAllUsers = false;
    options.storageFormat = PropertiesFile::StorageFormat::storeAsXML;
    
    return options;
}
