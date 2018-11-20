/*
 ==============================================================================
 
 Shapes.cpp
 Created: 4 Jun 2018 9:32:08pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#include "Shapes.h"
#include "../Definitions/Definitions.h"

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
        addPath.setFill(AuditionColours::black);
        addPath.setStrokeThickness(UI::shapeStrokeThickness);
        addPath.setPath(p);
        
        return addPath;
    }
    
    const DrawablePath remove ()
    {
        Path p;
        p.startNewSubPath(0, 5);
        p.lineTo(10, 5);
        
        DrawablePath deletePath;
        deletePath.setFill(AuditionColours::black);
        deletePath.setStrokeThickness(UI::shapeStrokeThickness);
        deletePath.setPath(p);
        
        return deletePath;
    }
    
    const DrawablePath clear ()
    {
        Path p;
        p.startNewSubPath(0, 0);
        p.lineTo(10, 10);
        p.startNewSubPath(10, 0);
        p.lineTo(0, 10);

        DrawablePath clearPath;
        clearPath.setFill(AuditionColours::black);
        clearPath.setStrokeThickness(UI::shapeStrokeThickness);
        clearPath.setPath(p);
        
        return clearPath;
    }
    
    void stop (Graphics& graphicsThatDraws, Rectangle<float>& areaToDrawIn)
    {
        auto square = areaToDrawIn.withSizeKeepingCentre(areaToDrawIn.getWidth() / 2.2,
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
    
    const DrawablePath shuffle ()
    {
        Point<float> a(0,0),    b(10, 0),   c(40, 0),   d(50, 0),
                     e(0, 20),  f(10, 20),  g(40, 20),  h(50, 20);
        Point<float> left(-10, 0), right(10, 0), z(0, -2);
        
        Path p;
        p.startNewSubPath(a);
        p.lineTo(b);
        p.cubicTo(b + right, g + left, g);
        p.lineTo(h);
        p.lineTo(h + z);
        p.lineTo(g + z);
        p.cubicTo(g + z + left, b + z + right, b + z);
        p.lineTo(a + z);
        
        p.startNewSubPath(e);
        p.lineTo(f);
        p.cubicTo(f + right, c + left, c);
        p.lineTo(d);
        p.lineTo(d + z);
        p.lineTo(c + z);
        p.cubicTo(c + z + left, f + z + right, f + z);
        p.lineTo(e + z);
        
        DrawablePath shufflePath;
        shufflePath.setFill(AuditionColours::black);
        shufflePath.setStrokeThickness(UI::shapeStrokeThickness);
        shufflePath.setPath(p);
        
        return shufflePath;
    }
    
    const DrawablePath repeat ()
    {
        Path p;
        p.startNewSubPath(0, 0);
        p.lineTo(10, 10);
        
        DrawablePath repeatPath;
        repeatPath.setFill(AuditionColours::black);
        repeatPath.setStrokeThickness(UI::shapeStrokeThickness);
        repeatPath.setPath(p);
        
        return repeatPath;
    }
    
    const DrawablePath autostop ()
    {
        Path p;
        p.startNewSubPath(0, 0);
        p.lineTo(10, 10);
        
        DrawablePath autostopPath;
        autostopPath.setFill(AuditionColours::black);
        autostopPath.setStrokeThickness(UI::shapeStrokeThickness);
        autostopPath.setPath(p);
        
        return autostopPath;
    }
};
