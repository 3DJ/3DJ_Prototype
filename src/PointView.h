//
//  PointView.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_PointView_h
#define Kinect_3DJ_PointView_h
#include "ofMain.h"

class PointView : public ofBaseApp
{
 public:
  PointView();
  ~PointView();
    
  void drawParticles();
  void addPoint(float x, float y, float z);
  void clearData();
  void uploadDataToVbo();
    
  vector <ofVec3f> points;
  vector <ofVec3f> sizes;
    
  ofVbo vbo;
  ofShader shader;
  ofTexture texture;
};

#endif
