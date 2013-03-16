//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "BoxButton.h"

CBoxButton::CBoxButton(float centerX, float centerY, float centerZ, int boxSize, float redVal, float greenVal, float blueVal, float alphaVal, string soundName, float rotation)
{
    m_x = centerX;
    m_y = centerY;
    m_z = centerZ;
    m_size = boxSize;
    m_r = redVal;
    m_g = greenVal;
    m_b = blueVal;
    m_a = alphaVal;

    m_rotation = rotation;

    m_slideOffset = 0;
    m_isRepeat = false;
    m_toBeStop = false;
    m_pointsInArea = 0;
    m_pointThreshold = 2000;
    m_threshold = 10;
    m_type = ET_MusicSampleButton;
    m_soundPlayer.loadSound(soundName);
    m_datapool = &CDataPoolSimple::getInstance();
}

CBoxButton::CBoxButton()
{

}

CBoxButton::~CBoxButton()
{

}

void CBoxButton::render()  //Draw boxes and set color
{
    void *temp=0;
    float slideOffset = 0;
    m_datapool->getRefByName("slideOffset", temp);
    if ( temp != 0)
    {
        slideOffset = *(float*)temp;
    }       

    if ( slideOffset != 0 || m_slideOffset/50 != 0)
    {
        if ( slideOffset != 0){

            m_slideOffset = slideOffset;
        }
        else{
            if ( m_slideOffset >= 0 && m_slideOffset <= 200 )
            {
                m_slideOffset = m_slideOffset - 40;
            }
            else if( m_slideOffset < 0 && m_slideOffset >= -200 )
            {
                m_slideOffset = m_slideOffset + 40;
            }
            else if ( m_slideOffset < -200 ){
                m_slideOffset = m_slideOffset - 80;
                m_slideOffset = 0;
            }
            else if ( m_slideOffset > 200 ){
                m_slideOffset = m_slideOffset + 80;
            }

        }

        if ( m_slideOffset > 2000 || m_slideOffset < -2000)
        {
            m_slideOffset = 0;
        }

        {

            drawBox(m_slideOffset);
            drawBox(m_slideOffset - 2000);
            drawBox(m_slideOffset + 2000);
            // shut down the sound.
            m_soundPlayer.setLoop(false);
            m_soundPlayer.stop();
            m_soundPlayer.setPosition(0);
            m_isRepeat = false;
        }
    }
    else
    {
    ofSetLineWidth(2);
    if ( m_isRepeat && !isCurrentlyHit() )
    {// make it stop on next hit.
        m_toBeStop = true;

        ofPushMatrix();

        ofRotateY(m_rotation);
        ofTranslate(m_x, m_y, m_z);

        //Draw diamond inside Box to indicate its looping
        ofPushMatrix(); //draw fill
        ofSetColor(0,220,0,200);
        ofFill();
        ofSetSphereResolution(2);
        ofSphere(0,0,0, m_size * 0.25);
        ofPopMatrix();

        ofPushMatrix();  //draw wire frame
        ofSetColor(20,50,20);
        ofEnableSmoothing();
        ofNoFill();
        ofSetLineWidth(1);
        ofSphere(0,0,0, m_size * 0.25);
        ofPopMatrix();

        ofPopMatrix();
    }

    if ( m_isRepeat && isCurrentlyHit() )
    {// if check this signal, close repeat option.
        if ( m_toBeStop == true ){
            m_isRepeat = false;
            m_toBeStop = false;
        }
    }

    if ( isCurrentlyHit() || m_isRepeat) {
		// set the current hit button to hit mode.
		setHitMode();
        // handle the sound
        if ( !m_soundPlayer.getIsPlaying()){
            m_soundPlayer.setLoop(true);
            m_soundPlayer.play();
        }
    } else{
		// set the unhit button as default mode.
		setDefaultMode();
        // shut down the sound.
        m_soundPlayer.setLoop(false);
        m_soundPlayer.stop();
        m_soundPlayer.setPosition(0);
    }
    }
    clear(); //clear point count
}

void CBoxButton::update(double timeSinceLastUpdate)
{

}

float CBoxButton::swellAnimation()
{
    return (m_size/10) * cos(ofGetElapsedTimef()*15);
}

float CBoxButton::percentIncluded()
{
    return ofMap(m_pointsInArea, 0, m_pointThreshold, 0, 1);
}

bool CBoxButton::isCurrentlyHit()
{
    return (m_pointsInArea > m_threshold);
}

bool CBoxButton::isHit()
{
    return isCurrentlyHit() && !m_active;
}

void CBoxButton::clear()
{
    m_active = isCurrentlyHit();
    m_pointsInArea = 0;
}

bool CBoxButton::collisionTest( ofPoint point)
{
    bool result = false;

    if(  (point.z > m_z - m_size/2) && (point.z < m_z + m_size/2)
       &&(point.x > m_x - m_size/2) && (point.x < m_x + m_size/2) 
       &&(point.y > m_y - m_size/2) && (point.y < m_y + m_size/2)){
          m_pointsInArea++;
          result = true;
    }
    return result;
}

bool CBoxButton::collisionTest( ofPoint *pPoint)
{
    return collisionTest( *pPoint );        // call the collisionTest( ofPoint point)
}

bool CBoxButton::hitTest(float x, float y, float z)
{
    return isCurrentlyHit() && !m_active;
}

void CBoxButton::setDefaultMode()
{
	ofPushMatrix();
	ofEnableSmoothing();
	ofEnableAlphaBlending();
    ofRotateY(m_rotation);
    //ofTranslate(m_x, m_y, m_z);
	ofNoFill();
	ofSetColor(255,255,255,51);
	ofBox(m_x, m_y, m_z, m_size);
	ofDisableAlphaBlending();
	ofDisableSmoothing();
	ofPopMatrix();

}

void CBoxButton::setHitMode()
{
	ofPushMatrix();
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofRotateY(m_rotation);
	ofTranslate(m_x, m_y, m_z);
	ofSetColor(255, 255, 255, 51+ (204 * percentIncluded()));
	ofFill();
	ofBox(m_size + swellAnimation());
	ofNoFill();
	ofSetColor(255,51);
	ofBox(m_size + swellAnimation());
	ofDisableAlphaBlending();
	ofDisableSmoothing();
	ofPopMatrix();
}

bool CBoxButton::isLoopBox()
{
    return false;
}

void CBoxButton::drawBox( float offset )
{
    ofPushMatrix();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofRotateY(m_rotation);
    //ofTranslate(m_x, m_y, m_z);
    ofNoFill();
    ofSetColor(255,255,255,51);
    ofBox(m_x+offset, m_y, m_z, m_size);
    ofDisableAlphaBlending();
    ofDisableSmoothing();
    ofPopMatrix();
}

void CBoxButton::reloadSound(string soundName)
{
    m_soundPlayer.loadSound(soundName);
}
