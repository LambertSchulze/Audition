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
    changelogText << "- Overview Page for live listening to the effects\n";
    changelogText << "- reworked the internal ValueTree structure\n";
    changelogText << "(still work in proggress)\n";
    
    changelogText << "\nUpcoming Features:\n\n";
    changelogText << "- Random Button and Autostop Button (stopping playback after 5 seconds)\n";
    changelogText << "- Better looking GUI, Icons, Colours, (and maby Animations and Transitions in the future)\n";
    changelogText << "- Record Clips from an audio input (hardware players or software via rewire)\n";
    changelogText << "- Reworking the Effect Base class to incorporate: Reverb, Compression, different Filterdesigns\n";
    changelogText << "- Statistics overview\n";
    changelogText << "- A second kind of quiz for explicitly naming the effect\n";
    changelogText << "- Scaling effects: the audible effects geet harder to hear the more you hear them correct\n";
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
