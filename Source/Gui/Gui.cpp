/*
 ==============================================================================
 
 Gui.cpp
 Created: 1 Jun 2018 9:31:32pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "Gui.h"
#include "../Core/Shapes.h"
#include "../Core/TransportManager.h"
#include "../MainContentComponent.h"
#include "../WindowContainer/TitleScreen.h"
#include "../WindowContainer/OverviewScreen.h"
#include "../WindowContainer/QuickQuizScreen.h"

Gui::Gui (ValueTree& tree)
: fileList("File List", nullptr), transportComponent("Transport Component")
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
    headerButtons[0]->onClick = [this] {setPage(1);};
    headerButtons[1]->onClick = [this] {setPage(2);};
    headerButtons[2]->onClick = [this] {setPage(3);};
    headerButtons[3]->onClick = [this] {setPage(3);};
    
    addAndMakeVisible(&fileList);
    fileList.setLookAndFeel(&fllaf);
    fileList.setMultipleSelectionEnabled(false);
    
    fileList.getHeader().setLookAndFeel(&fllaf);
    fileList.getHeader().addColumn("Filename", 1, 150, 100, -1, (TableHeaderComponent::visible | TableHeaderComponent::resizable));
    fileList.getHeader().addColumn("Start", 2, 48, 48, 48, TableHeaderComponent::visible);
    fileList.getHeader().setStretchToFitActive(true);
    fileList.getHeader().setSize(UI::sidebarWidth, fileList.getRowHeight());
    
    fileSettingButtons.add(new DrawableButton{"Add Button", DrawableButton::ImageOnButtonBackground});
    fileSettingButtons.add(new DrawableButton{"Remove Button", DrawableButton::ImageOnButtonBackground});
    fileSettingButtons.add(new DrawableButton{"Clear Button", DrawableButton::ImageOnButtonBackground});
    fileSettingButtons.add(new DrawableButton{"Shuffle Button", DrawableButton::ImageOnButtonBackground});
    fileSettingButtons.add(new DrawableButton{"Repeat Button", DrawableButton::ImageOnButtonBackground});
    fileSettingButtons.add(new DrawableButton{"Autostop Button", DrawableButton::ImageOnButtonBackground});
    
    buttonImages.add(new DrawablePath(DrawShape::add()));
    buttonImages.add(new DrawablePath(DrawShape::remove()));
    buttonImages.add(new DrawablePath(DrawShape::clear()));
    buttonImages.add(new DrawablePath(DrawShape::shuffle()));
    buttonImages.add(new DrawablePath(DrawShape::repeat()));
    buttonImages.add(new DrawablePath(DrawShape::autostop()));
    
    for (int i = 0; i < fileSettingButtons.size(); i++) {
        addAndMakeVisible(fileSettingButtons[i]);
        fileSettingButtons[i]->setLookAndFeel(&fllaf);
        fileSettingButtons[i]->setImages(buttonImages[i]);
    }
    
    stretchBarLayout.setItemLayout (0, 210, -0.8, 210);
    stretchBarLayout.setItemLayout (1, 4, 4, 4);
    stretchBarLayout.setItemLayout (2, 150, -1.0, -0.65);
    
    stretchBar = new StretchableLayoutResizerBar (&stretchBarLayout, 1, true);
    addAndMakeVisible (stretchBar);
    stretchBar->setLookAndFeel(&fllaf);
    
    addAndMakeVisible(&transportComponent);
    transportComponent.setAlwaysOnTop(true);
    
    if (pages.isEmpty()) {
        pages.add(new TitleScreen());
        pages.add(new OverviewScreen(tree));
        pages.add(new QuickQuizScreen(tree));
        pages.add(new Component());
    }
    
    for (auto page : pages) {
        addAndMakeVisible(page);
        page->setVisible(false);
    }
    pages[0]->setVisible(true);
}

Gui::~Gui()
{
    setLookAndFeel(nullptr);
}

void Gui::paint(Graphics& g)
{
    auto width = getWidth();
    auto height = getHeight();
    
    auto b = getLocalBounds();
    auto header = b.removeFromTop(UI::headerHeight);
    auto sidebar = b.removeFromLeft(stretchBar->getRight() - stretchBar->getWidth());
    auto page = b;
    
    ColourGradient headerGradient = ColourGradient (laf.gradient1B, 0, 0, laf.gradient1A, 0, UI::headerHeight, false);
    g.setGradientFill(headerGradient);
    g.fillRect(header);
    
    const int rowHeight (fileList.getRowHeight());

    auto buttonrowArea (sidebar.removeFromBottom(UI::fileListButtonRowHeight));
    auto emptyArea (sidebar.withTrimmedTop(rowHeight * (fileList.getNumRows())));
    
    g.setColour(AuditionColours::lightergrey);
    g.fillRect(buttonrowArea.removeFromTop(1));
    g.fillRect(buttonrowArea.removeFromRight(1).withTrimmedTop(2).withTrimmedBottom(3));
    g.fillRect(sidebar.removeFromTop(rowHeight).removeFromRight(1).withTrimmedTop(2).withTrimmedBottom(3));
    
    g.setColour(AuditionColours::lightgrey);
    if (!(fileList.getNumRows() % 2)) g.fillRect(emptyArea.removeFromTop(rowHeight));
    while (!emptyArea.isEmpty()) {
        g.fillRect(emptyArea.removeFromTop(rowHeight).removeFromRight(1).withTrimmedTop(2).withTrimmedBottom(2));
        g.fillRect(emptyArea.removeFromTop(rowHeight));
    }
    
    if (fileList.getNumRows() < 1) {
        g.setColour(AuditionColours::lightergrey);
        g.drawText("Add an audio file to start listening.", 0, (getHeight() / (2*rowHeight))*rowHeight + (3 * rowHeight / 4 ), sidebar.getWidth(), rowHeight, Justification::horizontallyCentred);
    }
}

void Gui::resized()
{
    auto width = getWidth();
    auto height = getHeight();
    
    auto b = getLocalBounds();
    auto header = b.removeFromTop(UI::headerHeight);
    
    for (auto button : headerButtons) {
        button->setBounds(header.removeFromLeft(width/headerButtons.size())
                          .reduced(UI::headerMargin));
    }
    
    Component* componentsToStretch[] = {nullptr, stretchBar, nullptr};
    stretchBarLayout.layOutComponents (componentsToStretch, 3, 0, UI::headerHeight, width, height - UI::headerHeight, false, true);
    
    auto sidebar = b.removeFromLeft(stretchBar->getRight() - stretchBar->getWidth());
    auto fileListButtonRow = sidebar.removeFromBottom(UI::fileListButtonRowHeight).reduced(14, 5);
    
    fileSettingButtons[0]->setBounds(fileListButtonRow.removeFromLeft(UI::fileListButtonWidth));
    fileSettingButtons[1]->setBounds(fileListButtonRow.removeFromLeft(UI::fileListButtonWidth));
    fileSettingButtons[2]->setBounds(fileListButtonRow.removeFromRight(UI::fileListButtonWidth));
    
    fileList.setBounds(sidebar);
    
    b.removeFromLeft(stretchBar->getWidth());
    for (auto page : pages) {
        page->setBounds(b);
    }
    
    transportComponent.setBounds(b.removeFromBottom(UI::footerHeight * 1.5).withSizeKeepingCentre(300, UI::footerHeight));
    
    repaint();
}

// ====================================================================
void Gui::repaintGui()
{
    repaint();
};

void Gui::updateFileList()
{
    fileList.updateContent();
};

void Gui::selectRowInFileList (int number)
{
    fileList.selectRow(number);
};

void Gui::enableFileSettingButtons()
{
    fileSettingButtons[1]->setEnabled(true);
    fileSettingButtons[2]->setEnabled(true);
};

void Gui::disableFileSettingButtons()
{
    fileSettingButtons[1]->setEnabled(false);
    fileSettingButtons[2]->setEnabled(false);
};

TransportComponent* Gui::getTransportComponent()
{
    return &transportComponent;
}

void Gui::enableOriginalButton()
{
    transportComponent.setComponentState(TransportComponent::OriginalEnabled);
};

void Gui::enableEffectButton()
{
    transportComponent.setComponentState(TransportComponent::BothEnabled);
};

void Gui::disableEffectButton()
{
    transportComponent.setComponentState(TransportComponent::OriginalEnabled);
};

void Gui::disableTransportButtons()
{
    transportComponent.setComponentState(TransportComponent::Disabled);
};

void Gui::turnAllPlayButtonsOff()
{
    transportComponent.turnBothPlayButtonsOff();
};

void Gui::turnOriginalButtonOff()
{
    transportComponent.turnBothPlayButtonsOff();
};

void Gui::turnEffectButtonOff()
{
    transportComponent.turnBothPlayButtonsOff();
};

void Gui::turnOriginalButtonOn()
{
    transportComponent.turnOriginalPlayButtonOn();
}

void Gui::turnEffectButtonOn()
{
    transportComponent.turnEffectPlayButtonOn();
}

bool Gui::shouldPlayOriginal()
{
    return transportComponent.inOriginalMode();
};

// ==========================================================
void Gui::setPage(int page)
{
    for (auto page : pages) {
        page->setVisible(false);
    }
    pages[page]->setVisible(true);
}

void Gui::Register()
// adding Button::Listeners and the TableListBoxModel
{
    auto* ptr = this->getParentComponent();
    auto* owner = dynamic_cast<MainContentComponent*>(ptr);
    fileList.setModel(&(owner->fileManager));
    
    fileSettingButtons[0]->addListener(&(owner->fileManager));
    fileSettingButtons[1]->addListener(&(owner->fileManager));
    fileSettingButtons[2]->addListener(&(owner->fileManager));
    
    transportComponent.addChangeListener(&(owner->transport));
    //transportComponent.addChangeListener(TransportManager::instance);
}
