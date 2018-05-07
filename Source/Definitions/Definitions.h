/*
  ==============================================================================

    Definitions.h
    Created: 5 Mar 2018 8:51:56pm
    Author:  Lambert Schulze

  ==============================================================================
*/

#ifndef __Definitions__
#define __Definitions__

#pragma once

namespace UI {
    const int headerHeight          = 80;
    const int sidebarWidth          = 200;
    const int footerHeight          = 100;
}

namespace IDs
{    
    const Identifier Main           = "MAIN";
    // saves the window height for next startup
    const Identifier WindowHeight   = "Window_Height";
    // saves the window width for next startup
    const Identifier WindowWidth    = "Window_Width";
    
    
    const Identifier Transport      = "TRANSPORT";
    // is set to Starting/Stopping by Play/Stop Buttons.
    // MainContentComponent manages playback if this is changed.
    const Identifier TransportState = "Transport_State";
    // Is set by effect Play/Stop Buttons.
    // MainContentComponents shouldProcessEffect flag is set after this to be checked by getNextAudioBlock.
    const Identifier IsProcessing   = "Effect_Is_Audible";
    // Is set at different places. MainContentComponent sets its currentEffect after this.
    // If its value is null (at startup), the effect Buttons should be disabled.
    const Identifier EffectToPlay   = "Effect_To_Play";
    // needs to be implemented...
    const Identifier LimitPlayback  = "Limit_Playback";
    
    
    const Identifier FileList       = "FILELIST";
    // stores the last selected file, so that at startup it can be selected again.
    const Identifier SelectedFile   = "Selected_File";
    
    
    const Identifier File           = "FILE";
    const Identifier FileName       = "File_Name";
    const Identifier FilePath       = "File_Path";
    const Identifier FileStart      = "Start_Playback";
    const Identifier IsLossless     = "Is_Lossless";
    
    const Identifier EffectList     = "EFFECTLIST";
    
    const Identifier Effect         = "EFFECT";
    const Identifier Number         = "Number";
    const Identifier EffectType     = "Effect_Type";
    const Identifier EffectName     = "Effect_Name";
    const Identifier Level          = "Level";
    const Identifier forPlayback    = "For_Playback";
    
    const Identifier Quiz           = "QUIZ";
    const Identifier QuizState      = "Quiz_State";
    const Identifier RoundCounter   = "Round_Counter";
    const Identifier WonRounds      = "Won_In_Round";
    const Identifier LostRounds     = "Lost_In_Round";
    const Identifier PlayerChoice   = "Player_Choice";
    
    const Identifier Choice          = "CHOICE";
    const Identifier Name           = "Name";
    const Identifier isRight        = "Is_Right";
    
    const Identifier Statistics     = "STATISTICS";
    const Identifier TotalPlayed    = "Total_Games_Played";
    const Identifier TotalWon       = "Total_Games_Won";
    const Identifier TotalLost      = "Total_Games_Lost";
};

#endif
