//
//  CEQView.cpp
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "EQView.h"

CEQView::CEQView()
{
    m_fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++) {
        m_fftSmoothed[i] = 0;
    }

    m_nBandsToGet = 128;
}

CEQView::~CEQView()
{
    if(m_fftSmoothed) delete m_fftSmoothed;
}

//========================================================================DRAW
void CEQView::drawEQRect()
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
    float width = (float) (5*128) / m_nBandsToGet;

    for(int i = 2; i<m_nBandsToGet; i++){
        // Use negative height here because it will be flipped top corner is (0,0)

        float height = m_fftSmoothed[i] * (ofGetHeight()-200);
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


void CEQView::soundUpdate()
{
    ofSoundUpdate();

    float * val = ofSoundGetSpectrum(m_nBandsToGet);
    for (int i = 0; i<m_nBandsToGet; i++) {
        //let the smoothed value sink to zero
        m_fftSmoothed[i] *= 0.96f; //Creates an animated drop back to zero
        if (m_fftSmoothed[i] < val[i]) m_fftSmoothed[i] = val[i];
    }
}
