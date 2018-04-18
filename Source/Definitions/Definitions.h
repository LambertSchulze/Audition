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
    const Identifier WindowHeight   = "Window_Height";
    const Identifier WindowWidth    = "Window_Width";
    
    const Identifier Transport      = "TRANSPORT";
    const Identifier TransportState = "Transport_State";
    const Identifier IsProcessing   = "Effect_Is_Audible";
    const Identifier EffectToPlay   = "Effect_To_Play";
    const Identifier LimitPlayback  = "Limit_Playback";
        
    const Identifier FileList       = "FILELIST";
    const Identifier LastSelected   = "Last_File_Selected";
    
    const Identifier File           = "FILE";
    const Identifier FileName       = "File_Name";
    const Identifier FilePath       = "File_Path";
    const Identifier Start          = "Start_Playback";
    const Identifier IsLossless     = "Is_Lossless";
    const Identifier Selected       = "Selected";
    
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