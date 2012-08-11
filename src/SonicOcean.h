//
//  SonicOcean.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/30/12.
//
//

#ifndef Kinect_3DJ_SonicOcean_h
#define Kinect_3DJ_SonicOcean_h
#include "ofMain.h"

class SonicOcean : public ofBaseApp
{
 public:
    
  SonicOcean();
  ~SonicOcean();
    
  void drawEQSonicOcean();
  void soundUpdate();
    
  float * fftSmoothed;
  int nBandsToGet;
    
  ofMesh mesh;
  int rows;
  int cols;
  int step;
    
  float heightThresh;
    
};

#endif
