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

namespace UI
{
    const int headerHeight          = 80;
    const int headerMargin          = 16;
    
    const int sidebarWidth          = 300;
    
    const int footerHeight          = 68;
    const int footerMargin          = 8;
    
    const int fileListButtonRowHeight   = 33;
    const int fileListButtonWidth       = 28;
    
    const float shapeStrokeThickness     = 0.35;
};

namespace AuditionColours {
    const Colour
            black       {0, 0, 0},
            grey        {142, 142, 145},
            lightergrey {205, 205, 208},
            lightgrey   {242, 242, 245},
            white       {255, 255, 255},
    
            blue        {27, 173, 248},
            brown       {162, 132, 94},
            green       {99, 218, 56},
            orange      {255, 149, 0},
            pink        {255, 41, 104},
            purple      {204, 115, 225},
            red         {255, 59, 48},
            yellow      {255, 204, 0};
}

#define TRANSPORT   vt.getChildWithName(IDs::Transport)
#define FILELIST    vt.getChildWithName(IDs::FileList)
#define EFFECTLIST  vt.getChildWithName(IDs::EffectList)
#define QUICKQUIZ   vt.getChildWithName(IDs::QuickQuiz)
#define STATISTICS  vt.getChildWithName(IDs::Statistics)

namespace IDs
{    
    const Identifier Main           = "MAIN";
    // saves the window height for next startup
    const Identifier WindowHeight   = "Window_Height";
    // saves the window width for next startup
    const Identifier WindowWidth    = "Window_Width";
    
    
    const Identifier Transport      = "TRANSPORT";
    // is set to Starting/Stopping by Play/Stop Buttons.
    const Identifier LimitPlayback  = "Limit_Playback";
    
    
    const Identifier FileList       = "FILELIST";
    // set the rules with wich after each quiz the next file is choosen
    const Identifier Repeat         = "Repeat";
    const Identifier Shuffle        = "Shuffle";
    
    
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

    
    const Identifier QuickQuiz      = "QUICKQUIZ";
    const Identifier RightEffect    = "Right_Effect";
    const Identifier WrongEffectA   = "Wrong_EffectA";
    const Identifier WrongEffectB   = "Wrong_EffectB";
    const Identifier RightButton    = "Right_Button_Num";
    const Identifier WrongButtonA   = "Wrong_ButtonA_Num";
    const Identifier WrongButtonB   = "Wrong_ButtonB_Num";

    
    const Identifier Player         = "PLAYER";
    // the number of the button that the player chose
    const Identifier Choice         = "Choice";

    
    const Identifier Statistics     = "STATISTICS";
    const Identifier TotalPlayed    = "Total_Games_Played";
    const Identifier TotalWon       = "Total_Games_Won";
    const Identifier TotalLost      = "Total_Games_Lost";
};

#endif
