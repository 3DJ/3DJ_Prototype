//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 10/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_COgreThread_h
#define Kinect_3DJ_COgreThread_h

#include <iostream>

#include "ofThread.h"
#include "XnOS.h"
#include "ofMain.h"
#include "COgreMain.h"
#include "DataPool.h"
using namespace DataPool;

class COgreThread : public ofThread
{
    public:
        COgreThread();
        ~COgreThread();
    private:
        void threadedFunction();

        COgreMain* m_ogreMain;
};

#endif
