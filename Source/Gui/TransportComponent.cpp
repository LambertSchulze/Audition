/*
  ==============================================================================
    TransportComponent.cpp
    Created: 14 May 2018 12:28:13pm
    Author:  Lambert Schulze
  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TransportComponent.h"

//==============================================================================
TransportComponent::TransportComponent(ValueTree& tree)
:   vt(tree)
{
    vt.addListener(this);
    labelShowingOriginal = true;
    
    updateState();
}

TransportComponent::~TransportComponent()
{
    vt.removeListener(this);
}

void TransportComponent::paint(Graphics& g)
{
    int height = this->getHeight();
    int width  = this->getWidth();
    auto lBBounds = this->getLocalBounds().removeFromLeft(height).toFloat();
    auto rBBounds = this->getLocalBounds().removeFromRight(height).toFloat();
    auto gradient = ColourGradient(Colour(52, 143, 80), 0, 0, Colour(86, 180, 211), width, height, true);
    g.setFont(g.getCurrentFont().withStyle(1));

    //drawing plain background colour
    g.setColour(lookAndFeel.laf.lightergrey);
    g.fillAll();
    g.setColour(lookAndFeel.laf.lightgrey);
    g.fillEllipse(lBBounds);
    g.fillEllipse(rBBounds);
    g.fillRect(height/2, 0, width-height, height);
    g.setColour(lookAndFeel.laf.white);
    g.fillEllipse(lBBounds.reduced(3));
    
    // draw disabled state
    if (state == Disabled) {
        //draw grey play heads
        g.setColour(lookAndFeel.laf.lightergrey);
        paintTriangle(g, lBBounds, false);
        paintTriangle(g, rBBounds, false);
    }
    
    if (state == OriginalEnabled) {
        g.setGradientFill(gradient);
        g.drawText("ORIGINAL", 0, 0, width, height, Justification::centred);
        if (TRANSPORT[IDs::TransportState] == "Playing") paintSquare(g, lBBounds);
        if (TRANSPORT[IDs::TransportState] == "Stopped") paintTriangle(g, lBBounds, true);
        g.setColour(lookAndFeel.laf.lightergrey);
        paintTriangle(g, rBBounds, false);
    }
    
    if (state == BothEnabled) {
        if (labelShowingOriginal) {
            g.setGradientFill(gradient);
            g.drawText("ORIGINAL", 0, 0, width, height, Justification::centred);
            if (TRANSPORT[IDs::TransportState] == "Playing") paintSquare(g, lBBounds);
            if (TRANSPORT[IDs::TransportState] == "Stopped") paintTriangle(g, lBBounds, true);
            //g.setColour(lookAndFeel.laf.grey);
            paintTriangle(g, rBBounds, true);
        }
        else {
            g.setGradientFill(gradient);
            g.fillEllipse(lBBounds);
            g.fillEllipse(rBBounds);
            g.fillRect(height/2, 0, width-height, height);
            g.setColour(lookAndFeel.laf.white);
            g.fillEllipse(rBBounds.reduced(3));
            g.drawText("EFFECT", 0, 0, width, height, Justification::centred);
            paintTriangle(g, lBBounds, true);
            g.setGradientFill(gradient);
            if (TRANSPORT[IDs::TransportState] == "Playing") paintSquare(g, rBBounds);
            if (TRANSPORT[IDs::TransportState] == "Stopped") paintTriangle(g, rBBounds, true);
            //g.setColour(lookAndFeel.laf.grey);
            //paintTriangle(g, lBBounds, true);
        }
    }
}

void TransportComponent::resized()
{
    auto r (getLocalBounds());
}

void TransportComponent::valueTreePropertyChanged (ValueTree& changedTree, const Identifier& property)
{
    // if there is a selected effect
    if (property == IDs::EffectToPlay && changedTree.hasProperty(IDs::EffectToPlay)) {
        state = BothEnabled;
        //DBG("Control fully enabled");   
    }
    // if the effect for playback got removed
    else if (changedTree.hasType(IDs::Transport) && !changedTree.hasProperty(IDs::EffectToPlay)) {
        state = OriginalEnabled;
    }
    repaint();
}

void TransportComponent::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childTree)              { updateState(); }
void TransportComponent::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childTree, int index) { updateState(); }
void TransportComponent::valueTreeChildOrderChanged (ValueTree& parentTree, int oldIndex, int newIndex) {}
void TransportComponent::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) {}
void TransportComponent::valueTreeRedirected (ValueTree& treeWhichHasBeenChanged) {}

void TransportComponent::mouseDown (const MouseEvent& event)
{
    if (state != Disabled && this->getLocalBounds().removeFromLeft(this->getHeight()).contains(event.getMouseDownPosition())) originalButtonClicked();

    if (state == BothEnabled && this->getLocalBounds().removeFromRight(this->getHeight()).contains(event.getMouseDownPosition())) effectButtonClicked();
}

void TransportComponent::originalButtonClicked()
{
    // if Button is enabled
    if (state != Disabled) {
        // if original is playing
        if (TRANSPORT[IDs::TransportState] == "Playing" && (bool) TRANSPORT[IDs::IsProcessing] == false) {
            // stop playback
            TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
        }
        // if effect is playing
        else if (TRANSPORT[IDs::TransportState] == "Playing" && (bool) TRANSPORT[IDs::IsProcessing] == true) {
            // start original playback
            TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
            switchLabelText(true);
            TRANSPORT.setProperty(IDs::IsProcessing, false, nullptr);
            TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
        }
        // if nothing is playing
        else if (TRANSPORT[IDs::TransportState] == "Stopped") {
            // start original playback
            switchLabelText(true);
            TRANSPORT.setProperty(IDs::IsProcessing, false, nullptr);
            TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
        }
    }
    repaint();
}

void TransportComponent::effectButtonClicked()
{
    // if Button is enabled
    if (state == BothEnabled) {
        // if effect is playing
        if (TRANSPORT[IDs::TransportState] == "Playing" && (bool) TRANSPORT[IDs::IsProcessing] == true) {
            // stop playback
            TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
        }
        // if original is playing
        else if (TRANSPORT[IDs::TransportState] == "Playing" && (bool) TRANSPORT[IDs::IsProcessing] == false) {
            // start effect playback
            TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
            switchLabelText(false);
            TRANSPORT.setProperty(IDs::IsProcessing, true, nullptr);
            TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
        }
        // if nothing is playing
        else if (TRANSPORT[IDs::TransportState] == "Stopped") {
            // start effect playback
            switchLabelText(false);
            TRANSPORT.setProperty(IDs::IsProcessing, true, nullptr);
            TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
        }
    }
    repaint();
}

void TransportComponent::paintTriangle(Graphics& g, Rectangle<float>& r, bool isFilled)
{
    float rad    = r.getHeight() / 2;
    float side   = rad * 1.1;
    float height = (side * 1.73) / 2;
    auto pos     = r.getPosition();
    auto pointA  = Point<float>(pos.getX()+(rad - height/3), pos.getY()+(rad + side/2));
    auto pointB  = Point<float>(pos.getX()+(rad + (2*height/3)), pos.getY()+(rad));
    auto pointC  = Point<float>(pos.getX()+(rad - height/3), pos.getY()+(rad - side/2));
    
    Path p;
    p.startNewSubPath(pointA);
    p.lineTo(pointB);
    p.lineTo(pointC);
    p.closeSubPath();
    
    if (isFilled)   g.fillPath(p);
    else            g.strokePath(p, PathStrokeType(2));
}

void TransportComponent::paintSquare(Graphics& g, Rectangle<float>& r)
{
    auto square = r.withSizeKeepingCentre(r.getWidth()/2.2, r.getHeight()/2.22);
    
    Path p;
    p.startNewSubPath(square.getTopLeft());
    p.lineTo(square.getTopRight());
    p.lineTo(square.getBottomRight());
    p.lineTo(square.getBottomLeft());
    p.closeSubPath();
    
    g.fillPath(p);
}

void TransportComponent::switchLabelText (bool toOriginal)
{
    labelShowingOriginal = toOriginal;
    repaint();
}

void TransportComponent::updateState()
{
    if (FILELIST.getNumChildren() > 0) state = State::OriginalEnabled;
    else state = State::Disabled;
    repaint();
}
