//
//  CWorld.cpXYZ
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CWorld.h"


CurrentState g_currentState;

CWorld::CWorld()
{   
}

CWorld::~CWorld()
{    
   
}

bool CWorld::init(IController* controller, IView* view )
{
    m_controller = controller;
    m_view = view;
    return true;
}

void CWorld::render()
{
    if ( m_view != 0)
    {
        m_view->draw();
    }    
}

void CWorld::update(double time_since_last_update)
{
    if ( m_controller != 0)
    {
        m_controller->update();    
    }
}


