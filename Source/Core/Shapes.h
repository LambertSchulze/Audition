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
    const DrawablePath add ()
    {
        Path p;
        p.startNewSubPath(0, 5);
        p.lineTo(10, 5);
        p.startNewSubPath(5, 0);
        p.lineTo(5, 10);
        
        DrawablePath addPath;
        addPath.setPath(p);
        addPath.setFill(Colours::black);
        
        return addPath;
    }
    
    const DrawablePath remove ()
    {
        Path p;
        p.startNewSubPath(0, 5);
        p.lineTo(10, 0);
        
        DrawablePath deletePath;
        deletePath.setPath(p);
        deletePath.setFill(Colours::black);
        
        return deletePath;
    }
    
    const DrawablePath clear ()
    {
        Path p;
        p.startNewSubPath(0, 5);
        p.lineTo(10, 5);
        p.startNewSubPath(5, 0);
        p.lineTo(5, 10);
        auto rotation = AffineTransform().rotated(45);
        p.applyTransform(rotation);
        
        DrawablePath clearPath;
        clearPath.setPath(p);
        clearPath.setFill(Colours::black);
        
        return clearPath;
    }
    
    void stop (Graphics& graphicsThatDraws, Rectangle<float>& areaToDrawIn)
    {
        auto square = areaToDrawIn.withSizeKeepingCentre(
                        areaToDrawIn.getWidth() / 2.2,
                        areaToDrawIn.getHeight() / 2.2);
        
        Path p;
        p.startNewSubPath(square.getTopLeft());
        p.lineTo(square.getTopRight());
        p.lineTo(square.getBottomRight());
        p.lineTo(square.getBottomLeft());
        p.closeSubPath();
        
        graphicsThatDraws.fillPath(p);
    }
    
    void play (Graphics& graphicsThatDraws, Rectangle<float>& areaToDrawIn)
    {
        const Path triangle = trianglePath(areaToDrawIn);
        
        graphicsThatDraws.fillPath(triangle);
    }
    
    void playOutline (Graphics& graphicsThatDraws, Rectangle<float>& areaToDrawIn)
    {
        const Path triangle = trianglePath(areaToDrawIn);
        auto pathStroke = PathStrokeType(2);
        
        graphicsThatDraws.strokePath(triangle, pathStroke);
    }
    
    void shuffle (Graphics& graphicsThatDraws, Rectangle<float>& areaToDrawIn)
    {
        auto topLeft = areaToDrawIn.getTopLeft();
        auto topRight = areaToDrawIn.getTopRight();
        auto bottomLeft = areaToDrawIn.getBottomLeft();
        auto bottomRight = areaToDrawIn.getBottomRight();
        
        Path p;
        p.startNewSubPath(topLeft);
        p.cubicTo(topRight, bottomLeft, bottomRight);
        p.startNewSubPath(bottomLeft);
        p.cubicTo(bottomRight, topLeft, topRight);
    }
};
