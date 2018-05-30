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
WindowContainer::WindowContainer(ValueTree& tree)
:   vt(tree),
    overviewScreen(vt), quickQuizScreen(vt),
    overviewButton ("Overview Screen Button"), quizButton ("Quiz Screen Button"),
    statisticsButton ("Statistics Sreen Button"), aboutButton ("About Screen Button")
{
    addAndMakeVisible(&titleScreen);
    addAndMakeVisible(&overviewScreen);
    addAndMakeVisible(&quickQuizScreen);
    addAndMakeVisible(&overviewButton);
    addAndMakeVisible(&quizButton);
    addAndMakeVisible(&statisticsButton);
    addAndMakeVisible(&aboutButton);
    
    overviewScreen  .setVisible(false);
    quickQuizScreen .setVisible(false);
    overviewButton  .setButtonText("Library");
    quizButton      .setButtonText("Practise");
    statisticsButton.setButtonText("Statistics");
    aboutButton     .setButtonText("About");
    overviewButton  .setClickingTogglesState(true);
    statisticsButton.setClickingTogglesState(true);
    aboutButton     .setClickingTogglesState(true);
    quizButton      .setClickingTogglesState(true);
    overviewButton  .setRadioGroupId(7);
    quizButton      .setRadioGroupId(7);
    statisticsButton.setRadioGroupId(7);
    aboutButton     .setRadioGroupId(7);
    overviewButton  .setLookAndFeel(&lookAndFeel);
    quizButton      .setLookAndFeel(&lookAndFeel);
    statisticsButton.setLookAndFeel(&lookAndFeel);
    aboutButton     .setLookAndFeel(&lookAndFeel);
    overviewButton  .addListener(this);
    quizButton      .addListener(this);
    statisticsButton.addListener(this);
    aboutButton     .addListener(this);
}

WindowContainer::~WindowContainer()
{
    overviewButton  .removeListener(this);
    quizButton      .removeListener(this);
    statisticsButton.removeListener(this);
    aboutButton     .removeListener(this);
}

void WindowContainer::paint (Graphics& g)
{
    ColourGradient bg = ColourGradient(Colour(52, 143, 80), 0, 0, Colour(86, 180, 211), this->getWidth(), this->getHeight(), true);
    g.setGradientFill(bg);
    g.fillRect(0, 0, this->getWidth(), UI::headerHeight);
}

void WindowContainer::resized()
{   
    auto            r       (getBounds());
    auto            rWidth  (r.getWidth());
    auto            rHeight (r.getHeight());
    auto            header  (r.removeFromTop(UI::headerHeight));
    Rectangle<int>  page    (UI::sidebarWidth, UI::headerHeight, rWidth-UI::sidebarWidth, rHeight-UI::headerHeight-UI::footerHeight);
    page = page.reduced(16);

    overviewButton  .setBounds(header.removeFromLeft(rWidth / 7).reduced(16));
    quizButton      .setBounds(header.removeFromLeft(rWidth / 7).reduced(16));
    aboutButton     .setBounds(header.removeFromRight(rWidth / 7).reduced(16));
    statisticsButton.setBounds(header.removeFromRight(rWidth / 7).reduced(16));
    titleScreen     .setBounds(page);
    overviewScreen  .setBounds(page);
    quickQuizScreen .setBounds(page);
}

void WindowContainer::buttonClicked(Button* b)
{
    if (b == &overviewButton)
    {
        if (titleScreen.isVisible())        titleScreen.setVisible(false);
        if (quickQuizScreen.isVisible())    quickQuizScreen.setVisible(false);
        if (!overviewScreen.isVisible())    overviewScreen.setVisible(true);
    }
    if (b == &quizButton)
    {
        if (titleScreen.isVisible())        titleScreen.setVisible(false);
        if (overviewScreen.isVisible())     overviewScreen.setVisible(false);
        if (!quickQuizScreen.isVisible())   quickQuizScreen.setVisible(true);
    }
}
