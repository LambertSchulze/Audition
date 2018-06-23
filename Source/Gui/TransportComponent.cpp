/*
  ==============================================================================
    TransportComponent.cpp
    Created: 14 May 2018 12:28:13pm
    Author:  Lambert Schulze
  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TransportComponent.h"
#include "../Core/Shapes.h"
#include "../Definitions/Definitions.h"

//==============================================================================
TransportComponent::TransportComponent (String name)
{}

TransportComponent::~TransportComponent()
{}

void TransportComponent::paint(Graphics& g)
{
    int height = this->getHeight();
    int width  = this->getWidth();
    auto lBBounds = this->getLocalBounds().removeFromLeft(height).toFloat();
    auto rBBounds = this->getLocalBounds().removeFromRight(height).toFloat();
    auto gradient = ColourGradient(Colour(52, 143, 80), 0, 0, Colour(86, 180, 211), width, height, true);
    g.setFont(g.getCurrentFont().withStyle(1));

    //drawing plain background colour
    g.setColour(Colours::transparentWhite);
    g.fillAll();
    g.setColour(AuditionColours::lightgrey);
    g.fillEllipse(lBBounds);
    g.fillEllipse(rBBounds);
    g.fillRect(height/2, 0, width-height, height);
    g.setColour(AuditionColours::white);
    g.fillEllipse(lBBounds.reduced(3));
    
    if (componentState == Disabled) {
        g.setColour(AuditionColours::lightergrey);
        DrawShape::playOutline(g, lBBounds);
        DrawShape::playOutline(g, rBBounds);
    }
    
    if (componentState == OriginalEnabled) {
        g.setGradientFill(gradient);
        g.drawText("ORIGINAL", 0, 0, width, height, Justification::centred);
            if (originalHeadPressed) DrawShape::stop(g, lBBounds);
            else                     DrawShape::play(g, lBBounds);
        g.setColour(AuditionColours::lightergrey);
        DrawShape::playOutline(g, rBBounds);
    }
    
    if (componentState == BothEnabled) {
        if (labelShowingOriginal) {
            g.setGradientFill(gradient);
            g.drawText("ORIGINAL", 0, 0, width, height, Justification::centred);
                if (originalHeadPressed) DrawShape::stop(g, lBBounds);
                else                     DrawShape::play(g, lBBounds);
            DrawShape::play(g, rBBounds);
        }
        else {
            g.setGradientFill(gradient);
            g.fillEllipse(lBBounds);
            g.fillEllipse(rBBounds);
            g.fillRect(height/2, 0, width-height, height);
            g.setColour(AuditionColours::white);
            g.fillEllipse(rBBounds.reduced(3));
            g.drawText("EFFECT", 0, 0, width, height, Justification::centred);
            DrawShape::play(g, lBBounds);
            g.setGradientFill(gradient);
                if (effectHeadPressed) DrawShape::stop(g, rBBounds);
                else                   DrawShape::play(g, rBBounds);
        }
    }
}

void TransportComponent::resized()
{
    auto r (getLocalBounds());
}

void TransportComponent::mouseDown (const MouseEvent& event)
{    
    if (componentState != Disabled && this->getLocalBounds().removeFromLeft(this->getHeight()).contains(event.getMouseDownPosition())) {
        setButtonState(OriginalButtonPressed);
        sendChangeMessage();
    }

    else if (componentState == BothEnabled && this->getLocalBounds().removeFromRight(this->getHeight()).contains(event.getMouseDownPosition())) {
        setButtonState(EffectButtonPressed);
        sendChangeMessage();
    }
}

//==============================================================================
void TransportComponent::setComponentState (ComponentState& newState)
{
    componentState = newState;
    repaint();
}

void TransportComponent::setComponentState (int newState)
{
    componentState = (ComponentState) newState;
    repaint();
}

void TransportComponent::setButtonState(ButtonState& newState)
{
    buttonState = newState;
    
    if (buttonState == ButtonState::OriginalButtonPressed) turnOriginalPlayButtonOn();
    else if (buttonState == ButtonState::EffectButtonPressed) turnEffectPlayButtonOn();
    else if (buttonState == ButtonState::NoButtonPressed) turnBothPlayButtonsOff();
    
    repaint();
}

void TransportComponent::setButtonState(int newState)
{
    buttonState = (ButtonState) newState;
    
    if (buttonState == ButtonState::OriginalButtonPressed) turnOriginalPlayButtonOn();
    else if (buttonState == ButtonState::EffectButtonPressed) turnEffectPlayButtonOn();
    else if (buttonState == ButtonState::NoButtonPressed) turnBothPlayButtonsOff();
    
    repaint();
}

TransportComponent::ButtonState TransportComponent::getButtonState() const
{
    return buttonState;
}

int TransportComponent::getButtonStateAsInt() const
{
    return (int) buttonState;
}

bool TransportComponent::noButtonPressed() const
{
    return !(originalHeadPressed || effectHeadPressed);
}

bool TransportComponent::inOriginalMode() const
{
    return labelShowingOriginal;
}

bool TransportComponent::inEffectMode() const
{
    return !labelShowingOriginal;
}

//==============================================================================
void TransportComponent::turnBothPlayButtonsOff()
{
    originalHeadPressed = false;
    effectHeadPressed = false;
    repaint();
}

void TransportComponent::turnOriginalPlayButtonOn()
{
    originalHeadPressed = true;
    effectHeadPressed = false;
    switchLabelText(true);
    repaint();
}

void TransportComponent::turnEffectPlayButtonOn()
{
    originalHeadPressed = false;
    effectHeadPressed = true;
    switchLabelText(false);
    repaint();
}

void TransportComponent::switchLabelText (bool toOriginal)
{
    labelShowingOriginal = toOriginal;
    repaint();
}
