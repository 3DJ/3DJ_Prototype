//
//  BoxButton.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_BoxButton_h
#define Kinect_3DJ_BoxButton_h
#include "Entity.h"

class BoxButton : public BoxEntity
{

 public:
  BoxButton(float centerX, float centerY, float centerZ, int boxSize, 
            float redVal, float greenVal, float blueVal, float alphaVal, string soundName);
  BoxButton();
  ~BoxButton();
    
    
  void render();
  void update(double time_since_last_update);

  float swellAnimation();
  float percentIncluded();
  bool isCurrentlyHit();
  bool isHit();
  void clear();
  bool collisionTest(ofPoint point);
  bool collisionTest(ofPoint *_point);
    
  ofSoundPlayer soundPlayer;
    
 protected:
  bool hitTest(float x, float y, float z);
    
};

#endif
