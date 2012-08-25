//
//  BoxButton.h
//  Kinect_3DJ
//
//  Created by LJ on 8/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ControlBoxButton.h"

bool CLoopBoxButton::isLoopBox()
{
    return true;
}

bool CLoopBoxButton::collisionTest(ofPoint *pPoint)
{
    collisionTest( *pPoint );
}

bool CLoopBoxButton::collisionTest(ofPoint point)
{
    bool result = false;

    if( ((point.x > m_x - m_size/2) && (point.y > m_y - m_size/2) && (point.z > m_z - m_size/2))
        &&(point.x < m_x + m_size/2) && (point.y < m_y + m_size/2) && (point.z < m_z + m_size/2)){

            result = true;
            m_pointsInArea++;
    }        
    return result;
}