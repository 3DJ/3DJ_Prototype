//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "COgreThread.h"

COgreThread::COgreThread()
{
    m_ogreMain = new COgreMain();
}

COgreThread::~COgreThread()
{
    if( !m_ogreMain )
    {
        delete m_ogreMain;
    }
}

void COgreThread::threadedFunction()
{
    m_ogreMain->init();
}
