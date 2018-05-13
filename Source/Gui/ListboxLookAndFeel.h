/*
 ==============================================================================
 
 MainMenueLookAndFeel.h
 Created: 13 May 2018 8:51:56pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "AuditionLookAndFeel.h"

class ListboxLookAndFeel :     public LookAndFeel_V4
{
public:
    ListboxLookAndFeel()
    : highlightedRowColour(laf.blue), altRowColour(laf.lightgrey), bgTextColour(laf.lightergrey)
    {
        setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentWhite);
//        setColour(ListBox::ColourIds::outlineColourId, Colours::green);
        setColour(ListBox::ColourIds::textColourId, laf.black);
        
        setColour(TableHeaderComponent::ColourIds::textColourId, laf.black);
        setColour(TableHeaderComponent::ColourIds::backgroundColourId, Colours::transparentWhite);
        setColour(TableHeaderComponent::ColourIds::outlineColourId, laf.lightergrey);
        setColour(TableHeaderComponent::ColourIds::highlightColourId, laf.white);
        
//        setColour(Label::ColourIds::backgroundColourId, Colours::pink);
        setColour(Label::ColourIds::textColourId, laf.black);
        setColour(Label::ColourIds::outlineColourId, Colours::transparentWhite);
        setColour(Label::ColourIds::backgroundWhenEditingColourId, laf.white);
        setColour(Label::ColourIds::textWhenEditingColourId, laf.black);
        setColour(Label::ColourIds::outlineWhenEditingColourId, highlightedRowColour);
        
        setColour(TextEditor::ColourIds::highlightColourId, laf.blue.brighter());
        
        setColour(ScrollBar::ColourIds::thumbColourId, laf.grey);
        
        setColour(TextButton::ColourIds::buttonColourId, laf.lightergrey);
        setColour(TextButton::ColourIds::buttonOnColourId, laf.lightgrey);
        setColour(TextButton::ColourIds::textColourOffId, laf.black);
    };
    
    ~ListboxLookAndFeel()
    {
        
    };
    
    void drawTableHeaderBackground (Graphics& g, TableHeaderComponent& header) override
    {
        Rectangle<int> r (header.getLocalBounds());
        auto outlineColour = header.findColour (TableHeaderComponent::outlineColourId);
        
        g.setColour (outlineColour);
        g.fillRect (r.removeFromBottom (1));
        g.setColour (header.findColour (TableHeaderComponent::backgroundColourId));
        g.fillRect (r);
        g.setColour (outlineColour);
        
        for (int i = header.getNumColumns(true); --i >= 0;)
            g.fillRect (header.getColumnPosition(i).removeFromRight(1).withTrimmedTop(2).withTrimmedBottom(3));
    };
    
    void drawTableHeaderColumn (Graphics& g, TableHeaderComponent& header, const String& columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags) override
    {
        Rectangle<int> area (width, height);
        area.reduce (8, 0);
        
        g.setColour (header.findColour (TableHeaderComponent::textColourId));
        g.setFont (Font (height * 0.5f, Font::plain));
        g.drawFittedText (columnName, area, Justification::centredLeft, 1);
    };

    void drawLabel (Graphics& g, Label& label) override
    {
        g.fillAll (label.findColour (Label::backgroundColourId));
        
        if (! label.isBeingEdited())
        {
            const Font font (getLabelFont (label));
            
            g.setColour (label.findColour (Label::textColourId));
            g.setFont (font);
            
            Rectangle<int> textArea (label.getBorderSize().subtractedFrom (label.getLocalBounds()));
            textArea.setHeight(textArea.getHeight() + 2);
            
            g.drawFittedText (label.getText(), textArea, label.getJustificationType(), 1, label.getMinimumHorizontalScale());
            
            g.setColour (label.findColour (Label::outlineColourId));
            g.drawRect (label.getLocalBounds());
        }
    };
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        Rectangle<float> buttonArea = button.getLocalBounds().toFloat();
        int cornerSize          = 4;
        int outlineThickness    = 2;
        
        if (isButtonDown) {
            g.setColour(laf.white.withAlpha(0.8f));
            g.fillRoundedRectangle(buttonArea.reduced(outlineThickness/2), cornerSize);
        }
        
        else {
            //draw outline
            g.setColour (laf.white);
            g.drawRoundedRectangle(buttonArea, cornerSize, outlineThickness);
            //fill background
            g.setColour (backgroundColour);
            g.fillRoundedRectangle(buttonArea, cornerSize);
        }
    };
    
    AuditionLookAndFeel laf;
    
    Colour highlightedRowColour, altRowColour, bgTextColour;
};
