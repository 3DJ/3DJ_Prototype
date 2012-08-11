//
//  World.cpp
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "World.h"

World::World()
{
  //Set up Kinect// Enable ->video image calibration
  kinect.setRegistration(true);
	kinect.init();
	kinect.open();
	angle = 20; // 20 degree tilt on startup
	kinect.setCameraTiltAngle(angle);    
    
  //SET UP BUTTONS and add all buttons to world vector============
  //    x, y, z, box size, r, g, b, a, music sample name
  //==============================================================
  red = 255;
  green = 255;
  blue = 255;
  alpha = 30;
  boxSize= 200;
  boxCenterX = 200;
  boxCenterY = 200;
    
  //Row A
  a1_Button = new BoxButton(375, -250, 1000, boxSize,red,green,blue,alpha,"sounds/Melody/GuitarStrummin.wav");
  addBoxButton(a1_Button);
  a2_Button = new BoxButton(125, -250, 1000,boxSize,red,green,blue,alpha,"sounds/Melody/Piano.wav");
  addBoxButton(a2_Button);
  a3_Button = new BoxButton(-125,-250,1000,boxSize,red,green,blue,alpha,"sounds/Melody/GuitarPick.wav");
  addBoxButton(a3_Button);
  a4_Button = new BoxButton(-375, -250, 1000, boxSize, red,green,blue,alpha, "sounds/Melody/Blip_Melody_01.wav");
  a4_Button->soundPlayer.setVolume(0.60f);
  addBoxButton(a4_Button);
    
  //Row B
  b1_Button = new BoxButton(375, 0, 1000, boxSize,red,green,blue,alpha,"sounds/Effects/Warp_1.wav");
  addBoxButton(b1_Button);
  b2_Button = new BoxButton(125, 0, 1000, boxSize,red,green,blue,alpha,"sounds/Effects/Uplifter.wav");
  addBoxButton(b2_Button);
  b3_Button = new BoxButton(-125, 0, 1000,boxSize,red,green,blue,alpha,"sounds/Bass/BassSlap.wav");
  addBoxButton(b3_Button);
    
  b4_Button = new BoxButton(-375,0,1000,boxSize,red,green,blue,alpha,"sounds/Bass/NastyBass.wav");
  addBoxButton(b4_Button);
       
  //Row C
  c1_Button = new BoxButton(375, 250, 1000,boxSize,red,green,blue,alpha,"sounds/Effects/Vinyl_Scratch_01.wav");
  addBoxButton(c1_Button);
  c2_Button = new BoxButton(125, 250, 1000,boxSize, red,green,blue,alpha,"sounds/Effects/RemixCrazyScratch_FX_02.wav");
  addBoxButton(c2_Button);
  c3_Button = new BoxButton(-125, 250, 1000,boxSize,red,green,blue,alpha,"sounds/Beat/TimbalesMerged_1.wav");
  addBoxButton(c3_Button);
  c4_Button = new BoxButton(-375, 250,1000,boxSize,red,green,blue,alpha,"sounds/Beat/Wee_Kick.wav");
  addBoxButton(c4_Button);
    
  setInitialVolume(1.0f);
  m_scale =3;
    
  pointView = new PointView();
  easyCam = new ofEasyCam;
  //easyCam->setFov(40);
  //easyCam->setTarget(ofVec3f(ofGetWidth()/2,ofGetHeight()/2,0));
    
  equalizerView = new EQView;
  sonicOcean = new SonicOcean;
    
}

World::~World()
{
  for (int i = 0; i < m_boxButtons.size(); i++)
    {
      BoxButton * curr = m_boxButtons.at(i);
      if(curr) delete curr;
        
    }
    
  if(pointView) delete pointView;
    
  //Delete buttons
  if (a1_Button) delete a1_Button;
  if (a2_Button) delete a2_Button;
  if (a3_Button) delete a3_Button;
  if (a4_Button) delete a4_Button;
  if (b1_Button) delete b1_Button;
  if (b2_Button) delete b2_Button;
  if (b3_Button) delete b3_Button;
  if (b4_Button) delete b4_Button;
  if (c1_Button) delete c1_Button;
  if (c2_Button) delete c2_Button;
  if (c3_Button) delete c3_Button;
  if (c4_Button) delete c4_Button;
    
  if(easyCam) delete easyCam;
  if(equalizerView) delete equalizerView;
  if(sonicOcean) delete sonicOcean;
}

void World::render()
{    
  easyCam->begin();
    
  //================================================================
  //Set up translation for all drawing
  //================================================================
  ofPushMatrix();
  ofScale(-1, 1);
  ofTranslate((ofGetWidth()/2)-320, (ofGetHeight()/2) -240, -1000); // center the points a bit
  ofRotateX(180);                   //Rotate around Axis
    
  ofTranslate(0,0,1000);            // Move back into Camera View
  ofTranslate(m_scale ,m_scale, m_scale *-800);
  ofScale(m_scale,m_scale,m_scale);
  //================================================================Translation Start
    
  for(int i = 0; i < m_boxButtons.size(); i++){
    BoxButton * curr = m_boxButtons.at(i);
        
    if(!curr) continue;
    curr->render(); // Draw BoxButtons
        
    //Handle Sound
    if (!curr->isCurrentlyHit()) {
      curr->soundPlayer.setLoop(false);
      curr->soundPlayer.stop();
      curr->soundPlayer.setPosition(0);
    }else if (!curr->soundPlayer.getIsPlaying()) {
      curr->soundPlayer.setLoop(true);
      curr->soundPlayer.play();
    }
        
    curr->clear(); //clear point count
  }

  drawDepthPointsAndTestHits(); // Do both here so we only look up the kinect data once...
    
  ofPopMatrix();
    
  ofTranslate(0, -1.5*ofGetHeight(), -5000);
  sonicOcean->drawEQSonicOcean();//EQ OCEAN
    
    
  //EndTranslation ================================================ Translation End
    
  easyCam->end();
    
  equalizerView->drawEQRect();

}

void World::update(double time_since_last_update)
{
    
	ofBackground(100, 100, 100);
  //ofBackgroundGradient(ofColor(0), ofColor(25,22,10));
    
  kinect.update();
  equalizerView->soundUpdate();
  sonicOcean->soundUpdate();
}

void World::drawDepthPointsAndTestHits() 
{
  int w = 640;
	int h = 480;
    
  ofPoint *XYZ, p;
    
	int step = 5;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			if(kinect.getDistanceAt(x, y) > 0) {
				p = kinect.getWorldCoordinateAt(x, y);
                
        if (p.z > 615 && p.z < 2000) {
          XYZ = &p;
          handleCollisions(XYZ); //check for hits for all buttons
          pointView->addPoint(p.x, p.y, p.z);
        }
			}
		}
	}
    
  pointView->uploadDataToVbo();
  pointView->drawParticles();
  pointView->clearData();
}


void World::addBoxButton(BoxButton * _boxButton)
{
  m_boxButtons.push_back(_boxButton);
}

void World::handleCollisions(ofPoint *XYZ)
{
  for(int i = 0; i < m_boxButtons.size(); i++){
    BoxEntity * curr = m_boxButtons.at(i);
        
    if(!curr) continue;
    curr->collisionTest(XYZ); //test Each Box for hits
  }
}

void World::clearButtons()
{
  for(int i = 0; i < m_boxButtons.size(); i++){
    BoxEntity * curr = m_boxButtons.at(i);
    if(!curr) continue;
    curr->clear();
  }
}

void World::setInitialVolume(float volumeLevel)
{
  for(int i = 0; i < m_boxButtons.size(); i++){
    BoxButton * curr = m_boxButtons.at(i);
        
    if(!curr) continue;
    curr->soundPlayer.setVolume(volumeLevel); 
  }
    
}
