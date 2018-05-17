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
TransportComponent::TransportComponent(ValueTree& vt)
:   tree(vt)
{
    
    state = State::OriginalEnabled;
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
        paintTriangle(g, lBBounds, true);
        g.setColour(lookAndFeel.laf.lightergrey);
        paintTriangle(g, rBBounds, false);
    }
}

void TransportComponent::resized()
{
    auto r (getLocalBounds());
}

void TransportComponent::valueTreePropertyChanged (ValueTree& changedTree, const Identifier& property) {}
void TransportComponent::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childTree) {}
void TransportComponent::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childTree, int index) {}
void TransportComponent::valueTreeChildOrderChanged (ValueTree& parentTree, int oldIndex, int newIndex) {}
void TransportComponent::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) {}
void TransportComponent::valueTreeRedirected (ValueTree& treeWhichHasBeenChanged) {}

void TransportComponent::originalButtonClicked()
{
    DBG("Play Original Button clicked");  
}

void TransportComponent::effectButtonClicked()
{
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

void TransportComponent::paintSquare(Graphics& g, Rectangle<float>& r)
{
    g.fillRect(r.withSizeKeepingCentre(r.getWidth()/2.7, r.getWidth()/2.7));
}
