//
//  CEQView.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_EQView_h
#define Kinect_3DJ_EQView_h
#include "ofMain.h"

class CEQView : public ofBaseApp
{
public:

    CEQView();
    ~CEQView();
    void drawEQRect();
    void soundUpdate();

private:
    float * m_fftSmoothed;
    int m_nBandsToGet;
};


#endif
