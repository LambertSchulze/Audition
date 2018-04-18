/*
  ==============================================================================

    TitleScreen.cpp
    Created: 18 Mar 2018 9:32:08pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TitleScreen.h"

//==============================================================================
TitleScreen::TitleScreen()
{    
    addAndMakeVisible(&textEditor);
    textEditor.setMultiLine(true);
    textEditor.setReadOnly(true);
    textEditor.setCaretVisible(false);
    
    String changelogText;
    
    changelogText << "AUDITION - Technical Hearing\n";
    changelogText << "********* Alpha1.0 *********\n\n";
    changelogText << "\nChangelog:\n\n";
    changelogText << "- removed some bugs and added things\n";
    changelogText << "(still work in proggress)\n";
    
    changelogText << "\nUpcoming Features:\n\n";
    changelogText << "- Overview Page for live listening to the effects\n";
    changelogText << "- Better looking GUI, Icons, Animations and Transitions\n";
    changelogText << "- Record Clips from an audio input (hardware players or software via rewire)\n";
    changelogText << "- Adding effects: Reverb, Compression, different Filterdesigns\n";
    changelogText << "- Statistics overview\n";
    changelogText << "- Tutorial for learning about the effects with progreesion mode\n";
    
    textEditor.setText(changelogText);
}

TitleScreen::~TitleScreen()
{}

void TitleScreen::paint (Graphics& g)
{}

void TitleScreen::resized()
{
    textEditor.setBounds(getLocalBounds().reduced(10));
}