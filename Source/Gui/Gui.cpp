/*
 ==============================================================================
 
 Gui.cpp
 Created: 1 Jun 2018 9:31:32pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Definitions.h"
#include "Gui.h"

Gui::Gui()
{
    headerButtons.add(new TextButton{"Overview Screen"});
    headerButtons.add(new TextButton{"QuickQuiz Screen"});
    headerButtons.add(new TextButton{"Statistics Screen"});
    headerButtons.add(new TextButton{"About Screen"});
    
    for (auto button : headerButtons) {
        addAndMakeVisible(button);
        button->setClickingTogglesState(true);
        button->setRadioGroupId(777);
        button->setLookAndFeel(&mmlaf);
    }
    headerButtons[0]->setButtonText("Library");
    headerButtons[1]->setButtonText("Practise");
    headerButtons[2]->setButtonText("Statistics");
    headerButtons[3]->setButtonText("About");
}

Gui::~Gui()
{
    
}

void Gui::paint(Graphics& g)
{
    auto width = getWidth();
    auto height = getHeight();
    
    auto b = getLocalBounds();
    auto header = b.removeFromTop(UI::headerHeight);
    auto footer = b.removeFromBottom(UI::footerHeight);
    auto sidebar = b.removeFromLeft(UI::sidebarWidth);
    auto page = b;
    
    ColourGradient headerGradient = ColourGradient (laf.gradient1A, 0, 0, laf.gradient1B, this->getWidth(), UI::headerHeight, true);
    g.setGradientFill(headerGradient);
    g.fillRect(header);
    g.setColour(laf.lightergrey);
    g.fillRect(footer);
    
    g.setColour(laf.grey);
    g.drawVerticalLine(UI::sidebarWidth - 1, height-UI::footerHeight+UI::footerMargin, height-UI::footerMargin);
}

void Gui::resized()
{
    auto width = getWidth();
    auto height = getHeight();
    
    auto b = getLocalBounds();
    auto header = b.removeFromTop(UI::headerHeight);
    auto footer = b.removeFromBottom(UI::footerHeight);
    auto sidebar = b.removeFromLeft(UI::sidebarWidth);
    auto page = b;
    
    for (auto button : headerButtons) {
        button->setBounds(header.removeFromLeft(width/headerButtons.size()).reduced(UI::headerMargin));
    }
}

void Gui::setupAreas()
{

}
