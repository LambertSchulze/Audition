/*
  ==============================================================================

    PlayStopButton.h
    Created: 21 Mar 2018 12:28:13pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Definitions/Definitions.h"

//==============================================================================
/*
 */
class PlayStopButton :  public ImageButton
{
public:
    PlayStopButton(String name);
    ~PlayStopButton();
    
    void paint (Graphics& g) override;
};
