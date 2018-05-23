/*
  ==============================================================================

    PlayStopButton.cpp
    Created: 21 Mar 2018 12:28:13pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PlayStopButton.h"

//==============================================================================
PlayStopButton::PlayStopButton(String name, ValueTree& tree)
:   ImageButton(name), vt(tree)
{
    this->setClickingTogglesState(true);
    
    drawPlayImageOnButton();
}

PlayStopButton::~PlayStopButton()
{}

void PlayStopButton::clicked()
{
    auto b = this->getToggleState();
    
    if (b == true)  drawStopImageOnButton();
    else            drawPlayImageOnButton();
    repaint();
    
    int choiceEffect = (int) QUICKQUIZ.getChildWithName(IDs::Player)[IDs::Choice];
    // if choice playing
    if (TRANSPORT[IDs::TransportState] == "Playing" && (int) TRANSPORT[IDs::EffectToPlay] == choiceEffect) {
        // stop playback
        TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
        TRANSPORT.removeProperty(IDs::EffectToPlay, nullptr);
    }
    // if nothing playing
    else if (TRANSPORT[IDs::TransportState] == "Stopped") {
        // start choice playback
        TRANSPORT.setProperty(IDs::IsProcessing, true, nullptr);
        TRANSPORT.setProperty(IDs::EffectToPlay, choiceEffect, nullptr);
        TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
    }
    // if original or effect playing
    else if (TRANSPORT[IDs::TransportState] == "Playing") {
        // stop playback and start choice playback
        TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
        TRANSPORT.setProperty(IDs::IsProcessing, true, nullptr);
        TRANSPORT.setProperty(IDs::EffectToPlay, choiceEffect, nullptr);
        TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
    }
}

void PlayStopButton::valueTreePropertyChanged (ValueTree& changedTree, const Identifier& changedValue)
{
    if (changedTree[changedValue] == "Stopping") this->setStateToOff();
}

void PlayStopButton::valueTreeChildAdded (ValueTree&, ValueTree&)               {}
void PlayStopButton::valueTreeChildRemoved (ValueTree&, ValueTree&, int)        {}
void PlayStopButton::valueTreeChildOrderChanged (ValueTree&, int, int)          {}
void PlayStopButton::valueTreeParentChanged (ValueTree&)                        {}
void PlayStopButton::valueTreeRedirected (ValueTree&)                           {}

void PlayStopButton::drawStopImageOnButton()
{
    Image image (Image::RGB, 100, 100, true);
    Graphics g(image);
    
    auto r (image.getBounds().toFloat());
    auto square = r.withSizeKeepingCentre(r.getWidth()/2.2, r.getHeight()/2.22);
    
    g.setColour(Colours::black);
    g.fillEllipse(0, 0, 100, 100);
    g.setColour(Colours::lightgrey);
    
    Path p;
    p.startNewSubPath(square.getTopLeft());
    p.lineTo(square.getTopRight());
    p.lineTo(square.getBottomRight());
    p.lineTo(square.getBottomLeft());
    p.closeSubPath();
    g.fillPath(p);
    
    this->setImages(false, true, true,
                    image, 0.7f, Colours::transparentBlack,
                    image, 1.0f, Colours::transparentBlack,
                    image, 1.0f, Colours::transparentBlack, 0.5);
}

void PlayStopButton::drawPlayImageOnButton()
{
    Image image (Image::RGB, 100, 100, true);
    Graphics g(image);
    
    float rad    = 100 / 2;
    float side   = rad * 1.1;
    float height = (side * 1.73) / 2;
    auto pos     = Point<float>(0.0, 0.0);
    auto pointA  = Point<float>(pos.getX()+(rad - height/3), pos.getY()+(rad + side/2));
    auto pointB  = Point<float>(pos.getX()+(rad + (2*height/3)), pos.getY()+(rad));
    auto pointC  = Point<float>(pos.getX()+(rad - height/3), pos.getY()+(rad - side/2));
    
    g.setColour(Colours::black);
    g.fillEllipse(0, 0, 100, 100);
    g.setColour(Colours::lightgrey);
    
    Path p;
    p.startNewSubPath(pointA);
    p.lineTo(pointB);
    p.lineTo(pointC);
    p.closeSubPath();
    g.fillPath(p);
    
    this->setImages(false, true, true,
                    image, 0.7f, Colours::transparentBlack,
                    image, 1.0f, Colours::transparentBlack,
                    image, 1.0f, Colours::transparentBlack, 0.5);
}

void PlayStopButton::setStateToOff()
{
    this->setToggleState(false, dontSendNotification);
    this->clicked();
}
