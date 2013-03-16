//
//  CWorld.cpXYZ
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CWorld.h"

// only this global variable. it will be replaced by datapool member.
CurrentState g_currentState;

CWorld::CWorld()
{   
    m_controller = 0;
    m_view = 0;
}

CWorld::~CWorld()
{    
   if ( m_controller )
   {
       delete m_controller;
   }
   
   if ( m_view )
   {
       delete m_view;
   }
}

bool CWorld::init(IController* controller, IView* view )
{
    m_controller = controller;
    m_view = view;
    return true;
}

void CWorld::draw()
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


