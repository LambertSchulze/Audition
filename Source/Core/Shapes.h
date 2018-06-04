/*
 ==============================================================================
 
 Shapes.h
 Created: 3 Jun 2018 9:32:08pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

namespace
{
    const Path trianglePath (Rectangle<float> areaThatContainsTriangle)
    {
        float rad    = areaThatContainsTriangle.getHeight() / 2;
        float side   = rad * 1.1;
        float height = (side * 1.73) / 2;
        auto pos     = areaThatContainsTriangle.getPosition();
        auto pointA  = Point<float>(pos.getX()+(rad - height/3), pos.getY()+(rad + side/2));
        auto pointB  = Point<float>(pos.getX()+(rad + (2*height/3)), pos.getY()+(rad));
        auto pointC  = Point<float>(pos.getX()+(rad - height/3), pos.getY()+(rad - side/2));
        
        Path p;
        p.startNewSubPath(pointA);
        p.lineTo(pointB);
        p.lineTo(pointC);
        p.closeSubPath();
        
        return p;
    }
};

namespace DrawShape
{
    const DrawablePath add ();
    const DrawablePath remove ();
    const DrawablePath clear ();
    
    void stop (Graphics& graphicsThatDraws, Rectangle<float>& areaToDrawIn);
    void play (Graphics& graphicsThatDraws, Rectangle<float>& areaToDrawIn);
    void playOutline (Graphics& graphicsThatDraws, Rectangle<float>& areaToDrawIn);
    
    const DrawablePath shuffle ();
    const DrawablePath repeat ();
    const DrawablePath autostop ();
};
