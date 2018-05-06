/*
 ==============================================================================
 
 Shapes.h
 Created: 4 May 2018 22:00:00pm
 Author:  Lambert Schulze
 
 ==============================================================================
 */

#pragma once

struct Shapes
{
    Path path;
    
    Path addPath()
    {
        path.addLineSegment(Line<float>(50, 0, 50, 100), 5);
        path.addLineSegment(Line<float>(0, 50, 100, 50), 5);
        
        return path;
    }
};
