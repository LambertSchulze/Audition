/*
  ==============================================================================

    WindowContainer.cpp
    Created: 18 Mar 2018 9:31:32pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "WindowContainer.h"
#include "../Definitions/Definitions.h"

//==============================================================================
WindowContainer::WindowContainer(ValueTree& vt)
:   mainVT(vt),
    overviewScreen(vt), quizScreen(vt),
    overviewButton ("Overview Screen Button"), quizButton ("Quiz Screen Button")
{
    addAndMakeVisible(&titleScreen);
    addAndMakeVisible(&overviewScreen);
    addAndMakeVisible(&quizScreen);
    addAndMakeVisible(&overviewButton);
    addAndMakeVisible(&quizButton);
    overviewScreen  .setVisible(false);
    quizScreen      .setVisible(false);
    
    overviewButton  .addListener(this);
    quizButton      .addListener(this);
}

WindowContainer::~WindowContainer()
{
    overviewButton  .removeListener(this);
    quizButton      .removeListener(this);
}

void WindowContainer::paint (Graphics& g)
{}

void WindowContainer::resized()
{   
    auto            r       (getBounds());
    auto            rWidth  (r.getWidth());
    auto            rHeight (r.getHeight());
    auto            header  (r.removeFromTop(UI::headerHeight));
    Rectangle<int>  page    (UI::sidebarWidth, UI::headerHeight, rWidth-UI::sidebarWidth, rHeight-UI::headerHeight-UI::footerHeight);

    overviewButton  .setBounds(header.removeFromLeft(UI::headerHeight).reduced(10));
    quizButton      .setBounds(header.removeFromLeft(UI::headerHeight).reduced(10));
    titleScreen     .setBounds(page);
    overviewScreen  .setBounds(page);
    quizScreen      .setBounds(page);
}

void WindowContainer::buttonClicked(Button* b)
{
    if (b == &overviewButton)
    {
        if (titleScreen.isVisible())        titleScreen.setVisible(false);
        if (quizScreen.isVisible())         quizScreen.setVisible(false);
        if (!overviewScreen.isVisible())    overviewScreen.setVisible(true);
    }
    if (b == &quizButton)
    {
        if (titleScreen.isVisible())        titleScreen.setVisible(false);
        if (overviewScreen.isVisible())     overviewScreen.setVisible(false);
        if (!quizScreen.isVisible())        quizScreen.setVisible(true);
    }
}