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
    
    const Path playShape()
    {
        path.startNewSubPath(50, 0);
        path.addArc(0, 0, 100, 100, 0, 2 * MathConstants<float>::pi);
        
        path.addArc(1, 1, 98, 98, 0, 2 * MathConstants<float>::pi);

        
        return path;
    }
};
