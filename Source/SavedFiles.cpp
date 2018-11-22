#include "SavedFiles.h"
#include "Application.h"


static const auto WINDOW_STATE          = StringRef("WINDOW_STATE");
static const auto FULLSCREEN_STATE      = StringRef("FULLSCREEN_STATE");


SavedFiles::SavedFiles()
: windowProperties(Application::getApp().getPropertyFileOptions())
{}

SavedFiles::~SavedFiles()
{}

String SavedFiles::getWindowState()
{
    if (!windowProperties.containsKey(WINDOW_STATE))
    {
        auto area = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
        area = area.reduced(area.getHeight() / 20);
        
        if (area.isEmpty())
        {
            return "";
        }
        else
        {
            auto bounds = String(area.getX()) + " " + String(area.getY()) + " "
                          + String(area.getWidth()) + " " + String(area.getHeight());
            
            return bounds;
        }
    }
    else
        return windowProperties.getValue(WINDOW_STATE);
}

bool SavedFiles::getFullscreenState()
{
    return windowProperties.getBoolValue(FULLSCREEN_STATE);     // defaultReturnValue = false
}

void SavedFiles::setWindowState(String windowState)
{
    windowProperties.setValue(WINDOW_STATE, windowState);
}

void SavedFiles::setFullscreenState(bool isFullscreen)
{
    windowProperties.setValue(FULLSCREEN_STATE, isFullscreen);
}
