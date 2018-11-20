#include "StoredSettings.h"
#include "Application.h"


StoredSettings::StoredSettings()
: windowProperties(Application::getApp().getPropertyFileOptions())
{}

StoredSettings::~StoredSettings()
{}

String StoredSettings::getWindotState()
{
    
    
    return windowProperties.getValue("WindowState");
}
