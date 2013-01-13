//
//  CNavigationControlButtons.cpp
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 9/22/12.
//
//

#include "CNavigationControlButtons.h"

CNavigationControlButtons::CNavigationControlButtons()
{
    setupVariables();
}

CNavigationControlButtons::CNavigationControlButtons(string _songTitle)
{
    setupVariables();
    m_songTitle = _songTitle;
}

CNavigationControlButtons::~CNavigationControlButtons()
{
    
}

void CNavigationControlButtons::render()
{
    drawCircleStroke();
}

void CNavigationControlButtons::update(double time_since_last_update)
{
    m_total_time += time_since_last_update;
}

void CNavigationControlButtons::setupVariables()
{
    m_active = true;
    
    m_x = ofGetWindowWidth()/2;
    m_y = ofGetWindowHeight()/2;
    m_z = 500.0f;
    
    m_r = 0;
    m_g = 0;
    m_b = 0;
    m_a = 255;
    
    m_total_time = 0;
    m_type = ET_NavigationButtons;
    
    m_resolution  = 75;
    m_strokeWidth = 1;
    m_startAngle  = 25.0f;
    m_endAngle    = 325.0f;
    
    m_radius = ofGetScreenHeight()/2;
    if (m_radius > ofGetScreenWidth()/2) { m_radius = ofGetScreenWidth()/2;}
    m_radius *= 0.9f; //90% of window so it fits on screen
    
    float m_startAngle, m_endAngle;
    
    m_songTitle = "";
}


void CNavigationControlButtons::drawCircleStroke( ){
    float rad = 200.0f;
    float resolutionOfArc = ((m_endAngle - m_startAngle) / (2 * PI)) * m_resolution;
    float radiansPerSegment = (m_endAngle - m_startAngle) / resolutionOfArc;
    float angle = 0;
    
    ofPushMatrix();
    ofBeginShape();
    ofSetLineWidth(m_strokeWidth);
    ofSetColor(m_r, m_g, m_b,m_a);
    
    for( int i=0; i<resolutionOfArc; i++ ){
        angle = m_startAngle + i*radiansPerSegment;
        ofVertex(m_x + rad*cos(angle), m_y - m_radius*sin(angle));
        
    }
    ofVertex(m_x + m_radius*cos(m_endAngle), m_y - m_radius*sin(m_endAngle));
    int radius2 = m_radius - m_strokeWidth;
    ofVertex(m_x + radius2*cos(m_endAngle), m_y - radius2*sin(m_endAngle));
    
    for( int i=resolutionOfArc-1; i>=0; i-- ){
        angle = m_startAngle + i*radiansPerSegment;
        ofVertex(m_x + radius2*cos(angle), m_y - radius2*sin(angle));
    }
    
    ofEndShape(true);
    ofPopMatrix();
}

bool CNavigationControlButtons::collisionTest(ofPoint *point){
    //test for collisions
    return false;
}

void CNavigationControlButtons::windowSizeChanged()
{
    m_x = ofGetWindowWidth()/2;
    m_y = ofGetWindowHeight()/2;
    m_z = 500.0f;
    
    m_radius = ofGetScreenHeight()/2;
    if (m_radius > ofGetScreenWidth()/2) { m_radius = ofGetScreenWidth()/2;}
    m_radius *= 0.9f; //90% of window so it fits on screen
}



