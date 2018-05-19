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
    labelShowingOriginal = true;
    
    updateState();
}

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
//    if (changedTree[property] == "Stopping") {
//        TRANSPORT.setProperty(IDs::IsProcessing, false, nullptr);
//        TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
//        TRANSPORT.setProperty(IDs::IsProcessing, true, nullptr);
//        TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
//    }
//    repaint();
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
    if (state != Disabled) {
        if (TRANSPORT[IDs::TransportState] == "Playing" && (bool) TRANSPORT[IDs::IsProcessing] == false) {
            //already playing original, so stop
            TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
        }
        else if (TRANSPORT[IDs::TransportState] == "Playing" && (bool) TRANSPORT[IDs::IsProcessing] == true) {
            // already playing effect and start original playback
            TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
            switchLabelText(true);
            TRANSPORT.setProperty(IDs::IsProcessing, false, nullptr);
            TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
        }
    }
    repaint();
    DBG("Play Original Button clicked");  
}

void TransportComponent::effectButtonClicked()
{
    if (state == BothEnabled) {
        if (TRANSPORT[IDs::TransportState] == "Playing" && (bool) TRANSPORT[IDs::IsProcessing] == true) {
            // aleady playing effect
            TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
        }
        else if (TRANSPORT[IDs::TransportState] == "Playing" && (bool) TRANSPORT[IDs::IsProcessing] == false) {
            // already playing original, so stop playback and start effect playback
            TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
            switchLabelText(false);
            TRANSPORT.setProperty(IDs::IsProcessing, true, nullptr);
            TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
        }
    }
    repaint();
    DBG("Play Effect Button clicked");  
}

void TransportComponent::paintTriangle(Graphics& g, Rectangle<float>& r, bool isFilled)
{
    if (isFilled) {
        g.drawArrow(Line<float>(r.getX()+r.getWidth()/4, r.getCentreY(), r.getX()+r.getWidth()*3/4, r.getCentreY()), 0, r.getWidth()/2.2, r.getWidth()/2);
    }
    if (!isFilled) {
        // needs some attention!
        g.drawLine(r.getX()+r.getWidth()/4, (r.getHeight()-r.getWidth()/1.73)/2, r.getX()+r.getWidth()*3/4, r.getCentreY(), 2);
        g.drawLine(r.getX()+r.getWidth()/4, (r.getHeight()+r.getWidth()/1.73)/2, r.getX()+r.getWidth()*3/4, r.getCentreY(), 2);
        g.drawLine(r.getX()+r.getWidth()/4, (r.getHeight()+r.getWidth()/1.73)/2, r.getX()+r.getWidth()/4, (r.getHeight()-r.getWidth()/1.73)/2);
    }
}

void TransportComponent::paintSquare(Graphics& g, Rectangle<float>& r)  { g.fillRect(r.withSizeKeepingCentre(r.getWidth()/2.7, r.getWidth()/2.7)); }

void TransportComponent::switchLabelText (bool toOriginal)
{
    labelShowingOriginal = toOriginal;
    repaint();
}

void TransportComponent::updateState()
{
    if (FILELIST.getNumChildren() > 0) state = State::OriginalEnabled;
    else state = State::Disabled;
}
