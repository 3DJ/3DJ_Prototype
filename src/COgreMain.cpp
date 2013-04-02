//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "COgreMain.h"

COgreMain::COgreMain( )
{
    m_dataPool = &CDataPool::getInstance();
}

bool COgreMain::init()
{
    void* val;
    m_dataPool->getRefByName("testDataPool", val);
    std::cout<<"Ogre Thread"<<((string*)val)->c_str()<<std::endl;

    return true;
}

