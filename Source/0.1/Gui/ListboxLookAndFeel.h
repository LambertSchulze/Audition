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
        setColour(ListBox::ColourIds::textColourId, laf.black);
        
        setColour(TableHeaderComponent::ColourIds::textColourId, laf.black);
        setColour(TableHeaderComponent::ColourIds::backgroundColourId, Colours::transparentWhite);
        setColour(TableHeaderComponent::ColourIds::outlineColourId, laf.lightergrey);
        setColour(TableHeaderComponent::ColourIds::highlightColourId, laf.white);
        
        setColour(Label::ColourIds::textColourId, laf.black);
        setColour(Label::ColourIds::outlineColourId, Colours::transparentWhite);
        setColour(Label::ColourIds::backgroundWhenEditingColourId, laf.white);
        setColour(Label::ColourIds::textWhenEditingColourId, laf.black);
        setColour(Label::ColourIds::outlineWhenEditingColourId, highlightedRowColour);
        
        setColour(TextEditor::ColourIds::highlightColourId, laf.blue.brighter());
        
        setColour(ScrollBar::ColourIds::thumbColourId, laf.grey);
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
        area.reduce (14, 0);
        
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
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
        auto cornerSize = 4.0f;
        auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);
        
        if (isButtonDown) {
            g.setColour (laf.lightgrey);
            g.fillRoundedRectangle (bounds, cornerSize);
        }
        
        g.setColour (laf.lightergrey);
        g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
    };
    
    void drawScrollbar (Graphics& g, ScrollBar& scrollbar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override
    {
        ignoreUnused (isMouseDown);
        
        Rectangle<int> thumbBounds;
        
        if (isScrollbarVertical)
            thumbBounds = { x, thumbStartPosition, width, thumbSize };
        else
            thumbBounds = { thumbStartPosition, y, thumbSize, height };
        
        auto c = scrollbar.findColour (ScrollBar::ColourIds::thumbColourId);
        //g.setColour (isMouseOver ? c.brighter (0.25f) : c);
        g.fillRoundedRectangle (thumbBounds.reduced (1).toFloat(), 4.0f);
    };
    
    AuditionLookAndFeel laf;
    
    Colour highlightedRowColour, altRowColour, bgTextColour;
};
