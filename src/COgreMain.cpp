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

}

bool COgreMain::init( CDataPoolSimple* dataPool )
{
    m_dataPool = dataPool;

    void* val;
    m_dataPool->getRefByName("testThread", val);
    while(true){
        std::cout<<"Ogre Thread"<<*(string*)val<<std::endl;
    }

    return true;
}

