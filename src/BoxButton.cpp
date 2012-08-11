//
//  BoxButton.cpp
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "BoxButton.h"

BoxButton::BoxButton(float centerX, float centerY, float centerZ, int boxSize, float redVal, float greenVal, float blueVal, float alphaVal, string soundName)
{
  m_x = centerX;
  m_y = centerY;
  m_z = centerZ;
  m_size = boxSize;
  m_r = redVal;
  m_g = greenVal;
  m_b = blueVal;
  m_a = alphaVal;
    
  m_pointsInArea = 0;
  m_pointThreshold = 2000;
  m_threshold = 10;
  m_type = ET_MusicSampleButton;
  soundPlayer.loadSound(soundName);
}

BoxButton::BoxButton()
{
    
}

BoxButton::~BoxButton()
{
    
}

void BoxButton::render()  //Draw boxes and set color
{
  if (isCurrentlyHit()) {
    ofPushMatrix();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofTranslate(m_x, m_y, m_z);
    ofSetColor(255, 255, 255, 51+ (204 * percentIncluded()));
    //ofSetColor(0, 0, 0);
    ofFill();
    ofBox(m_size + swellAnimation());
    ofNoFill();
    ofSetColor(255);
    ofBox(m_size + swellAnimation());
    ofDisableAlphaBlending();
    ofDisableSmoothing();
    ofPopMatrix();
  } else {
    ofPushMatrix();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(m_r, m_g, m_b, m_a);
    ofFill();
    ofBox(m_x, m_y, m_z, m_size);
    ofNoFill();
    ofSetColor(255,255,255);
    ofBox(m_x, m_y, m_z, m_size);
    ofDisableAlphaBlending();
    ofDisableSmoothing();
    ofPopMatrix();
  }

}

void BoxButton::update(double time_since_last_update)
{

}

float BoxButton::swellAnimation()
{
  return (m_size/10) * cos(ofGetElapsedTimef()*15);   
}

float BoxButton::percentIncluded()
{
  return ofMap(m_pointsInArea, 0, m_pointThreshold, 0, 1);
}

bool BoxButton::isCurrentlyHit()
{
  return (m_pointsInArea > m_threshold);
}

bool BoxButton::isHit()
{
  return isCurrentlyHit() && !m_active;
}

void BoxButton::clear()
{
  m_active = isCurrentlyHit();
  m_pointsInArea = 0;
}

bool BoxButton::collisionTest(ofPoint point)
{
  bool result = false;
    
  if(point.x > m_x - m_size/2 && point.x < m_x + m_size/2){
    if(point.y > m_y - m_size/2 && point.y < m_y + m_size/2){
      if(point.z > m_z - m_size/2 && point.z < m_z + m_size/2){
        result = true;
        m_pointsInArea++;
      }
    }
  }
    
  return result;
    
}

bool BoxButton::collisionTest(ofPoint *_point)
{
  bool result = false;
    
  if(_point->x > m_x - m_size/2 && _point->x < m_x + m_size/2){
    if(_point->y > m_y - m_size/2 && _point->y < m_y + m_size/2){
      if(_point->z > m_z - m_size/2 && _point->z < m_z + m_size/2){
        result = true;
        m_pointsInArea++;
      }
    }
  }
    
  return result;
    
}

bool BoxButton::hitTest(float x, float y, float z)
{
  return isCurrentlyHit() && !m_active;
}
