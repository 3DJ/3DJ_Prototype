//
//  SnakeFish.cpp
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 10/12/12.
//
//

#include "SnakeFish.h"

SnakeFish::SnakeFish()
{
    m_active = true;
    m_x = 0.0f;
    m_y = 0.0f;
    m_z = 0.0f;
    m_r = 127;
    m_g = 255;
    m_b = 127;
    m_a = 127;
    m_total_time = 0.0f;
    m_type = ET_Creature;
    
    m_maxSpeed = ofRandom(8, 15);
    m_birth = 1;
    m_energy = 100.0f;
    m_power = 0.02;
    m_position = ofPoint(m_x, m_y, m_z);
    m_projectedPos = m_position;
    m_rotation = ofPoint(0,0,0);
    m_scale = ofPoint(1,1,1);
    
    m_sF = ofRandom(0.005, 0.01);
    m_rXF = ofRandom(0.005, 0.01);
    m_rYA = ofRandom(0.05, 0.15);
    m_rXA = ofRandom(0.05, 0.15);
    m_rYF = ofRandom(0.05, 0.15);

    m_oS = ofRandom(2*PI);
    m_oX = ofRandom(2*PI);
    m_oY = ofRandom(2*PI);
}

SnakeFish::~SnakeFish()
{

}

void SnakeFish::preRender()
{
    m_energy -= m_power;
    if(m_energy < 0) m_energy = 0;
    
}


void SnakeFish::render()
{
    ofPoint *p1 = new ofPoint(m_energy * m_position.x, m_energy * m_position.y, m_energy * m_position.z );
    m_queue.push_back(p1);
    
    ofBeginShape();
    for (int i = 0; i<m_queue.size();  i+=2) {
        ofVertex(m_position.x + i, m_position.y+ i, m_position.z + i);
    }
    ofEndShape();
}

void SnakeFish::postRender()
{
    
}

void SnakeFish::update(double time_since_last_update)
{
    
}

void SnakeFish::applyTransforms()
{
    
}

void SnakeFish::move()
{
    float speed = ofMap(sin(ofGetFrameNum() * m_sF + m_oS), -1, 1, 2, m_maxSpeed);
    
}

void SnakeFish::kill()
{
    m_energy = 0.0f;
}