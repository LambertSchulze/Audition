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
    
    shuffleDownImage->replaceColour(Colours::black, Colour(52, 143, 80).brighter());
    shuffleOnImage->replaceColour(Colours::black, Colour(52, 143, 80));
    repeatDownImage->replaceColour(Colours::black, Colour(52, 143, 80).interpolatedWith(Colour(86, 180, 211), 0.5).brighter());
    repeatOnImage->replaceColour(Colours::black, Colour(52, 143, 80).interpolatedWith(Colour(86, 180, 211), 0.5));
    autostopDownImage->replaceColour(Colours::black, Colour(86, 180, 211).brighter());
    autostopOnImage->replaceColour(Colours::black, Colour(86, 180, 211));
    
    addAndMakeVisible(&shuffleButton);
    addAndMakeVisible(&repeatButton);
    addAndMakeVisible(&autostopButton);
    addAndMakeVisible(&transport);
    shuffleButton   .setLookAndFeel(&lookAndFeel);
    repeatButton    .setLookAndFeel(&lookAndFeel);
    autostopButton  .setLookAndFeel(&lookAndFeel);
    transport       .setLookAndFeel(&tcLookAndFeel);
    
    shuffleButton   .setClickingTogglesState(true);
    repeatButton    .setClickingTogglesState(true);
    autostopButton  .setClickingTogglesState(true);
    
    shuffleButton   .setImages(shuffleImage, nullptr, shuffleDownImage, nullptr, shuffleOnImage, nullptr, shuffleDownImage);
    repeatButton    .setImages(repeatImage, nullptr, repeatDownImage, nullptr, repeatOnImage, nullptr, repeatDownImage);
    autostopButton  .setImages(autostopImage, nullptr, autostopDownImage, nullptr, autostopOnImage, nullptr, autostopDownImage);
    
    shuffleButton.onClick   = [this] { shuffleButtonclicked(); };
    repeatButton.onClick    = [this] { repeatButtonclicked(); };
    autostopButton.onClick  = [this] { autostopButtonclicked(); };
    
    shuffleButton.setToggleState(FILELIST[IDs::Shuffle], dontSendNotification);
    repeatButton.setToggleState(FILELIST[IDs::Repeat], dontSendNotification);
    autostopButton.setToggleState(TRANSPORT[IDs::LimitPlayback], dontSendNotification);
    
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
    auto leftRowArea (r.removeFromLeft(UI::sidebarWidth).reduced(14, UI::footerHeight / 4));
    
    shuffleButton   .setBounds(leftRowArea.removeFromLeft(leftRowArea.getWidth() / 3).withSizeKeepingCentre(leftRowArea.getHeight(), leftRowArea.getHeight()));
    repeatButton    .setBounds(leftRowArea.removeFromLeft(leftRowArea.getWidth() / 2).withSizeKeepingCentre(leftRowArea.getHeight(), leftRowArea.getHeight()));
    autostopButton  .setBounds(leftRowArea.withSizeKeepingCentre(leftRowArea.getHeight(), leftRowArea.getHeight()));
        transport.setBounds(getLocalBounds().withTrimmedLeft(UI::sidebarWidth).withSizeKeepingCentre(200, UI::footerHeight).reduced(6));
}

//==============================================================================
void TransportControl::valueTreePropertyChanged (ValueTree& changedTree, const Identifier& property) {}
void TransportControl::valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded) {}
void TransportControl::valueTreeChildRemoved (ValueTree &parentTree, ValueTree &childWhichHasBeenRemoved, int /*index*/) {}
void TransportControl::valueTreeChildOrderChanged (ValueTree&, int, int) {}
void TransportControl::valueTreeParentChanged (ValueTree&) {}
void TransportControl::valueTreeRedirected (ValueTree&) {}

//==============================================================================
void TransportControl::shuffleButtonclicked()
{
    //DBG("Shuffle Button clicked.");
    if ((bool) FILELIST[IDs::Shuffle] == true)
        FILELIST.setProperty(IDs::Shuffle, false, nullptr);
    else
        FILELIST.setProperty(IDs::Shuffle, true, nullptr);
}

void TransportControl::repeatButtonclicked()
{
//    DBG("Repeat Button clicked.");
    if ((bool) FILELIST[IDs::Repeat] == true)
        FILELIST.setProperty(IDs::Repeat, false, nullptr);
    else
        FILELIST.setProperty(IDs::Repeat, true, nullptr);
}

void TransportControl::autostopButtonclicked()
{
    //DBG("Debug Button clicked.");
    if ((bool) FILELIST[IDs::LimitPlayback] == true)
        FILELIST.setProperty(IDs::LimitPlayback, false, nullptr);
    else
        FILELIST.setProperty(IDs::LimitPlayback, true, nullptr);
}
