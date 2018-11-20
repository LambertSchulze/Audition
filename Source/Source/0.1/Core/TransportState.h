/*
 ==============================================================================
 
 TransportState.h
 Created: 10 Jun 2018 9:18:38pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class TransportState
{
public:
    TransportState() {};
    virtual ~TransportState() {};
    
    static enum State {STARTING_ORIGINAL = 0, STARTING_EFFECT = 1, PLAYING = 2, STOPPING = 3, STOPPED = 4} state;
    void setState (State newState)
    {
        state = newState;
        stateChanged();
    };
    State getState () const             { return state; };
    virtual void stateChanged () =0;

    static int playbackEffect;
    void setEffect (int newEffect)
    {
        playbackEffect = newEffect;
        effectChanged();
    };
    int getEffect () const              { return playbackEffect; };
    virtual void effectChanged () =0;
    
    static int startTime;
    void setStart (int startTime)       { this->startTime = startTime; };
    int getStart () const               { return startTime; };
    
    static String playbackFile;
    void setFile (String filePath)      { playbackFile = filePath; };
    String getFilePath () const         { return playbackFile; };
};
