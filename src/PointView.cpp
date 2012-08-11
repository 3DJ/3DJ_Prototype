//
//  PointView.cpp
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PointView.h"

PointView::PointView()
{
  ofDisableArbTex();
  ofLoadImage(texture, "dot.png");
  shader.load("shader");
}
PointView::~PointView()
{
    
}

void PointView:: drawParticles()
{
  ofPushMatrix();
  ofSetColor(50, 100, 5, 40);
  ofEnableAlphaBlending();
  ofEnableBlendMode(OF_BLENDMODE_ADD);
  ofEnablePointSprites();
    
  shader.begin();
    
  texture.bind();
  vbo.draw(GL_POINTS, 0, (int)points.size());
  texture.unbind();
  shader.end();
    
  ofDisablePointSprites();
  ofDisableBlendMode();
  ofDisableAlphaBlending();
    
  ofPopMatrix();   
}

void PointView:: addPoint(float x, float y, float z)
{
  ofVec3f p(x,y,z);
  points.push_back(p);
    
  //Pass the size in as a normal x position
  float size = ofRandom(25,50);
  sizes.push_back(size);
}

void PointView::clearData()
{
  points.clear(); //clear point data
  sizes.clear();
  vbo.clear();
}

void PointView::uploadDataToVbo()
{
  vbo.setVertexData(&points[0], (int)points.size(), GL_STATIC_DRAW);
  vbo.setNormalData(&sizes[0],(int)sizes.size(), GL_STATIC_DRAW);
}
