/*
  ==============================================================================

    TransportControl.cpp
    Created: 18 Mar 2018 9:19:16pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TransportControl.h"
#include "../Definitions/Definitions.h"

//==============================================================================
TransportControl::TransportControl (ValueTree& tree)
:   vt(tree),
    shuffleButton("Shuffle", DrawableButton::ButtonStyle::ImageFitted),
    repeatButton("Repeat", DrawableButton::ButtonStyle::ImageFitted),
    autostopButton("Autostop", DrawableButton::ButtonStyle::ImageFitted),
    originalButton("Original"), effectButton("Effect"),
    originalLabel("Original"), effectLabel("Effect"),
    transport(vt)
{
    ScopedPointer<Drawable> shuffleImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_shuffle_black_48px.svg"));
    ScopedPointer<Drawable> shuffleDownImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_shuffle_black_48px.svg"));
    ScopedPointer<Drawable> shuffleOnImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_shuffle_black_48px.svg"));
    
    ScopedPointer<Drawable> repeatImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_repeat_one_black_48px.svg"));
    ScopedPointer<Drawable> repeatDownImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_repeat_one_black_48px.svg"));
    ScopedPointer<Drawable> repeatOnImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_repeat_one_black_48px.svg"));
    
    ScopedPointer<Drawable> autostopImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_replay_5_black_48px.svg"));
    ScopedPointer<Drawable> autostopDownImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_replay_5_black_48px.svg"));
    ScopedPointer<Drawable> autostopOnImage = Drawable::createFromSVGFile(File("/Users/lambertschulze/Documents/Develop/Audition/Assets/buttons/ic_replay_5_black_48px.svg"));

    
    shuffleDownImage->replaceColour(Colours::black, Colours::white);
    shuffleOnImage->replaceColour(Colours::black, Colours::red);
    repeatDownImage->replaceColour(Colours::black, Colours::white);
    repeatOnImage->replaceColour(Colours::black, Colours::red);
    autostopDownImage->replaceColour(Colours::black, Colours::white);
    autostopOnImage->replaceColour(Colours::black, Colours::red);

    
    addAndMakeVisible(&shuffleButton);
    addAndMakeVisible(&repeatButton);
    addAndMakeVisible(&autostopButton);
    addAndMakeVisible(&originalButton);
    addAndMakeVisible(&effectButton);
    addAndMakeVisible(&originalLabel);
    addAndMakeVisible(&effectLabel);
    addAndMakeVisible(&transport);
    shuffleButton   .setLookAndFeel(&lookAndFeel);
    repeatButton    .setLookAndFeel(&lookAndFeel);
    autostopButton  .setLookAndFeel(&lookAndFeel);
    originalButton  .setLookAndFeel(&lookAndFeel);
    effectButton    .setLookAndFeel(&lookAndFeel);
    originalLabel   .setLookAndFeel(&lookAndFeel);
    effectLabel     .setLookAndFeel(&lookAndFeel);
    transport       .setLookAndFeel(&tcLookAndFeel);
    
    shuffleButton   .setClickingTogglesState(true);
    repeatButton    .setClickingTogglesState(true);
    autostopButton  .setClickingTogglesState(true);
    originalButton  .setClickingTogglesState(true);
    effectButton    .setClickingTogglesState(true);
    
    originalLabel   .setText("Original", dontSendNotification);
    originalLabel   .setJustificationType(Justification::centred);
    effectLabel     .setText("Effect", dontSendNotification);
    effectLabel     .setJustificationType(Justification::centred);
    
    shuffleButton   .setImages(shuffleImage, nullptr, shuffleDownImage, nullptr, shuffleOnImage, nullptr, shuffleDownImage);
    repeatButton    .setImages(repeatImage, nullptr, repeatDownImage, nullptr, repeatOnImage, nullptr, repeatDownImage);
    autostopButton  .setImages(autostopImage, nullptr, autostopDownImage, nullptr, autostopOnImage, nullptr, autostopDownImage);
    
    // originalButton should only be enabled if Filelist is not empty and a file is selected.
    // effectButton should only be enabled if a file is loaded and a effect for playback is set.
    // this has to be checked in the beginning and after every change of the properties.
    
    if (FILELIST.getNumChildren() == 0) originalButton.setEnabled(false);
    
    // the effect button is always disabled in the beginning.
    effectButton.setEnabled(false);

    shuffleButton.onClick   = [this] { shuffleButtonclicked(); };
    repeatButton.onClick    = [this] { repeatButtonclicked(); };
    autostopButton.onClick  = [this] { autostopButtonclicked(); };
    originalButton.onClick  = [this] { originalButtonclicked(); };
    effectButton.onClick    = [this] { effectButtonclicked(); };
    vt.addListener(this);
}

TransportControl::~TransportControl()
{
    vt.removeListener(this);
}

void TransportControl::paint (Graphics& g)
{
    g.setColour(lookAndFeel.laf.lightergrey);
    g.fillRect(0, 0, this->getWidth(), UI::footerHeight);
    
    g.setColour(lookAndFeel.laf.grey);
    g.drawVerticalLine(UI::sidebarWidth - 1, 8, UI::footerHeight - 8);
}

void TransportControl::resized()
{
    auto r (getLocalBounds());
    auto leftRowArea (r.removeFromLeft(UI::sidebarWidth).reduced(14, UI::footerHeight / 5));
    
    //control Buttons
    shuffleButton   .setBounds(leftRowArea.removeFromLeft(leftRowArea.getWidth() / 3).withSizeKeepingCentre(leftRowArea.getHeight(), leftRowArea.getHeight()));
    repeatButton    .setBounds(leftRowArea.removeFromLeft(leftRowArea.getWidth() / 2).withSizeKeepingCentre(leftRowArea.getHeight(), leftRowArea.getHeight()));
    autostopButton  .setBounds(leftRowArea.withSizeKeepingCentre(leftRowArea.getHeight(), leftRowArea.getHeight()));
    
    //PlayStopButtons
    auto l (r.removeFromLeft(r.getWidth() / 2));
    l = l.removeFromRight(100);
    r = r.removeFromLeft(100);
    
//    originalButton  .setBounds(l.removeFromTop(50));
//    originalLabel   .setBounds(l.withTrimmedTop(4));
//    effectButton    .setBounds(r.removeFromTop(50));
//    effectLabel     .setBounds(r.withTrimmedTop(4));
    
    transport.setBounds(getLocalBounds().withTrimmedLeft(UI::sidebarWidth).withSizeKeepingCentre(200, UI::footerHeight).reduced(6));
}

//==============================================================================
void TransportControl::valueTreePropertyChanged (ValueTree& changedTree, const Identifier& property)
{
    // disabling buttons in different QuizStates
    if (property == IDs::QuizState)
    {
        if ((int) changedTree.getProperty(property) == 3)
        {
            originalButton  .setEnabled(false);
            effectButton    .setEnabled(false);
        }
        if ((int) changedTree.getProperty(property) == 0)
        {
            originalButton  .setEnabled(true);
            effectButton    .setEnabled(true);
        }
    }
    
    // if no effect is set for playback, that means, Effect_To_Play has the value -1 (like at startup),
    // the effect button is dissabled. Otherwise its being enabled.
    if (property == IDs::EffectToPlay) {((int) changedTree.getProperty(property) == -1) ? effectButton.setEnabled(false) : effectButton.setEnabled(true);}
    
    // if playback stopps by removing the file from the list, the buttons must get untoggled manualy
    if (property == IDs::TransportState)
    {
        String s  = changedTree.getProperty(property);
        if (s == "Stopped") {
            originalButton.setStateToOff();
            effectButton  .setStateToOff();
            DBG("set the state of the playbuttons to false.");
        }
    }
}

void TransportControl::valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded)
{
    // makes shure that buttons get enabled if files are in the filelist.
    if (parentTree.hasType(IDs::FileList))  { originalButton.setEnabled(true); }
}

void TransportControl::valueTreeChildRemoved (ValueTree &parentTree, ValueTree &childWhichHasBeenRemoved, int /*index*/)
{
    // if all files of the filelist are removed, disables buttons
    if (parentTree.hasType(IDs::FileList)) {
        if (parentTree.getNumChildren() == 0) {
            originalButton  .setEnabled(false);
            effectButton    .setEnabled(false);}
    }
}

void TransportControl::valueTreeChildOrderChanged (ValueTree&, int, int) {}
void TransportControl::valueTreeParentChanged (ValueTree&) {}
void TransportControl::valueTreeRedirected (ValueTree&) {}

//==============================================================================
void TransportControl::shuffleButtonclicked()
{
    DBG("Shuffle Button clicked.");
}

void TransportControl::repeatButtonclicked()
{
    DBG("Repeat Button clicked.");
}

void TransportControl::autostopButtonclicked()
{
    DBG("Debug Button clicked.");
}

void TransportControl::originalButtonclicked()
{
    DBG("originalButton: clicked");
    if (originalButton.getToggleState())
    {
        TRANSPORT.setProperty(IDs::IsProcessing, false, nullptr);
        TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
        effectButton.setToggleState(false, dontSendNotification);
    }
    else
    {
        TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
    }
}

void TransportControl::effectButtonclicked()
{
    DBG("effectButton: clicked");
    if (effectButton.getToggleState())
    {
        TRANSPORT.setProperty(IDs::IsProcessing, true, nullptr);
        TRANSPORT.setProperty(IDs::TransportState, "Starting", nullptr);
        originalButton.setToggleState(false, dontSendNotification);
    }
    else
    {
        TRANSPORT.setProperty(IDs::TransportState, "Stopping", nullptr);
    }
}
