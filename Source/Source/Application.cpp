#include "Application.h"


Application::Application()
{}

void Application::initialise (const String& commandLine)
{
    storedSettings.reset (new StoredSettings());
    
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    ui.reset (new MainWindow(getApplicationName()));
}

PropertiesFile::Options Application::getPropertyFileOptions()
{
    PropertiesFile::Options options;
    options.applicationName = getApplicationName();
    options.filenameSuffix = ".settings";
    options.folderName = "";
    options.osxLibrarySubFolder = "Application Support";
    options.commonToAllUsers = false;
    options.storageFormat = PropertiesFile::StorageFormat::storeAsXML;
    
    return options;
}
