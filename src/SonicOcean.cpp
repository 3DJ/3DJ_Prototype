//
//  SonicOcean.cpp
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/30/12.
//
//

#include "SonicOcean.h"

SonicOcean::SonicOcean()
{
  //Set up fft Stuff
  fftSmoothed = new float[8192];
  for (int i = 0; i < 8192; i++) {
    fftSmoothed[i] = 0;
  }
    
    
  //Set up Mesh
  rows = 128;
  cols = 30;
  step = 80;
  mesh.addVertex(ofPoint( - (rows/2)*step + step,0,0));
  mesh.addColor(ofColor(ofRandom(80,120),255,ofRandom(80,120), 127));
    
  nBandsToGet = rows*2.5; // for FFT
  heightThresh = 1200;
    
  for(int r = 0; r < rows; ++r){
    for (int c = 0; c < cols; ++c){
            
            
      if ((r&1)==0) { //even rows
                
        //color
        ofColor color;
        //color.setHsb(20+ 25 * sin(r*c), 255, 255, 127);
        color.set(ofRandom(80,120), 255,ofRandom(80,120), 127);

        //point2
        ofVec3f p2(r*step,  0.0f, c*step);
        p2.x = p2.x - (rows/2)*step + step;
        mesh.addVertex(p2);
        mesh.addColor(color);
                
        p2.x = p2.x - (rows/2)*step + step;
                
        //point3
        ofVec3f p3(r*step - step, 0.0f, c*step + step);
        p3.x = p3.x - (rows/2)*step + step;
        mesh.addVertex(p3);
        mesh.addColor(color);
                
                
      } else { //odd rows
                
        //color
        ofColor color;
        //color.setHsb(20+ 25 * sin(r*c), 255, 255, 127);
        color.set(ofRandom(80,120), 255, ofRandom(80,120), 127);
                
        //point2
        ofVec3f p2(r*step, 0.0f, (cols-c)*step);
        p2.x = p2.x - (rows/2)*step + step;
        mesh.addVertex(p2);
        mesh.addColor(color);
                
        //point3
        ofVec3f p3(r*step - step, 0.0f, (cols-c)*step - step);
        p3.x = p3.x - (rows/2)*step + step;
        mesh.addVertex(p3);
        mesh.addColor(color);
                
      }
            
    }
  }
    
    
  mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

}

SonicOcean::~SonicOcean()
{
  if(fftSmoothed) delete fftSmoothed;
}

void SonicOcean::soundUpdate()
{
  ofSoundUpdate();
    
  float * val = ofSoundGetSpectrum(nBandsToGet);
  for (int i = 0; i<nBandsToGet; i++) {
    //let the smoothed value sink to zero
    fftSmoothed[i] *= 0.96f; //Creates an animated drop back to zero
    if (fftSmoothed[i] < val[i]) {fftSmoothed[i] = val[i];}
  }
}

void SonicOcean::drawEQSonicOcean()
{
  
  ofPushMatrix();
  ofEnableAlphaBlending();
    
  //Change the vertexes based on fft results
  for(int r = 0; r < rows*3; r++){
    for (int c = 0; c < cols-3; c++) {
      int index = c * r + c;
            
      ofVec3f tempVec = mesh.getVertex(index + 1);
      tempVec.y = fftSmoothed[r]*2000;
      if(tempVec.y> heightThresh){ tempVec.y = heightThresh;}
      mesh.setVertex(index + 1, tempVec);
            
      ofVec3f tempVec2 = mesh.getVertex(index+2);
      tempVec2.y = fftSmoothed[r]*2000;
      if(tempVec2.y > heightThresh){ tempVec2.y = heightThresh;}
      mesh.setVertex((index + 2), tempVec2);
                     
    }
  }
    
  mesh.drawFaces();
    
  mesh.disableColors(); //wireframe
  ofSetColor(0);
  mesh.drawWireframe();
  mesh.enableColors();
 
  ofPopMatrix();

}
