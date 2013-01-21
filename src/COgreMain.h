//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 10/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_COgreMain_h
#define Kinect_3DJ_COgreMain_h

#include <iostream>
#include "DataPool.h"
using namespace DataPool;

class COgreMain
{
    public:
        COgreMain();
        bool init( CDataPoolSimple* dataPool);
    private:
        CDataPoolSimple* m_dataPool;

};

#endif
