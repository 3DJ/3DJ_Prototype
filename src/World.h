//
//  World.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_World_h
#define Kinect_3DJ_World_h
#include "Entity.h"
#include "BoxButton.h"
#include "ofxKinect.h"
#include "PointView.h"
#include "EQView.h"
#include "SonicOcean.h"
#include <vector>

using namespace std;

//===========================================================
// Class : World
// The entire world in which all entities exist
//===========================================================
class World
{

 public:
    
  World();
  ~World();
    
  void render();
  void update(double time_since_last_update);
  void addBoxButton(BoxButton * _boxButton);
  void clearButtons();
  void handleCollisions(ofPoint * XYZ);
  void setInitialVolume(float volumeLevel);
  void drawDepthPointsAndTestHits();
    
    
  ofxKinect kinect;
    
  //Stuff For Buttons========================================
   
  BoxButton *a1_Button;
  BoxButton *a2_Button;
  BoxButton *a3_Button;
  BoxButton *a4_Button;
    
  BoxButton *b1_Button;
  BoxButton *b2_Button;
  BoxButton *b3_Button;
  BoxButton *b4_Button;
  
  BoxButton *c1_Button;
  BoxButton *c2_Button;
  BoxButton *c3_Button;
  BoxButton *c4_Button;
    
  double m_totalTime;
  int m_scale;
  int angle;
  int red,green, blue, alpha;
  int boxSize, boxCenterX, boxCenterY;
  vector<BoxButton *> m_boxButtons;    

  PointView * pointView;
  ofEasyCam *easyCam;
  EQView *equalizerView;
  SonicOcean *sonicOcean;
    
};

#endif
