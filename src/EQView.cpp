//
//  EQView.cpp
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "EQView.h"

EQView::EQView()
{
  fftSmoothed = new float[8192];
  for (int i = 0; i < 8192; i++) {
    fftSmoothed[i] = 0;
  }
    
  nBandsToGet = 128;
}

EQView::~EQView()
{
  if(fftSmoothed) delete fftSmoothed;
}

//========================================================================DRAW
void EQView::drawEQRect()
{
  ofPushMatrix();
  ofEnableAlphaBlending();
  //ofEnableBlendMode(OF_BLENDMODE_ADD);
  //Draw Window Rectangle
  ofSetColor(255, 255, 255,50);
  ofFill();
  ofRect(ofGetWidth()-(5*128)-50+10, 100, 5*128-10, ofGetHeight()-200);
  //ofSetColor(0);
   
  //Draw the fft results
  float width = (float) (5*128) / nBandsToGet;
    
  for(int i = 2; i<nBandsToGet; i++){
    // Use negative height here because it will be flipped top corner is (0,0)

    float height = fftSmoothed[i] * (ofGetHeight()-200);
    if (height > (ofGetHeight()-200)) height = ofGetHeight() - 200;
    if (height <5) height = 5;
        
      
    //ofNoFill();
    ofSetColor(0);
    //ofRect((ofGetWidth()-(5*128))+i*width-(50),ofGetHeight()-100,width,-height);
    ofFill();
    ofRect((ofGetWidth()-(5*128))+i*width-(50), ofGetHeight()-height-100,width,-5);
    //Draw Bottom Bar
    ofRect(ofGetWidth()-(5*128)-50+10, ofGetHeight()-105, 5*128-10, 8);
        
       
        
  }
    
  //Draw Text to Screen=====================================
  stringstream msg;
    
  msg
    << "3DJ Barcamp Demo" << endl
    << "FPS : " << ofToString(ofGetFrameRate()) << endl
    << "Song: Cham Culture" <<  endl
    << "Song Author: Tormod Englesaeth" <<  endl;
    
  ofDrawBitmapString(msg.str(), (ofGetWidth()-(5*128))+5, 150);
    
  //ofDisableBlendMode();
  ofDisableAlphaBlending();
  ofPopMatrix();    
}
//========================================================================


void EQView::soundUpdate()
{
  ofSoundUpdate();
    
  float * val = ofSoundGetSpectrum(nBandsToGet);
  for (int i = 0; i<nBandsToGet; i++) {
    //let the smoothed value sink to zero
    fftSmoothed[i] *= 0.96f; //Creates an animated drop back to zero
    if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
  }
}
