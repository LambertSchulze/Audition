//
//  QuickQuizScreen.cpp
//  Audition - App
//
//  Created by Lambert Schulze on 20.05.18.
//

#include "../../JuceLibraryCode/JuceHeader.h"
#include "QuickQuizScreen.h"

void QuickQuizState::switchState (QuickQuizScreen* c, int i) { c->currentState = c->stateList[i]; }
