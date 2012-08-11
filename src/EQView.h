//
//  EQView.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_EQView_h
#define Kinect_3DJ_EQView_h
#include "ofMain.h"

class EQView : public ofBaseApp
{
 public:
    
  EQView();
  ~EQView();
  void drawEQRect();
  void soundUpdate();
    
  float * fftSmoothed;
  int nBandsToGet;
};


#endif
