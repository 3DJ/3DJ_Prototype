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
    m_z = 500.0f;
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
    m_position = ofVec3f(m_x, m_y, m_z);
    m_projectedPos = m_position;
    m_rotation = ofVec3f(0,0,0);
    m_scale = ofVec3f(1,1,1);
    
    m_sF  = ofRandom(0.005, 0.01);
    m_rXF = ofRandom(0.005, 0.01);
    m_rYA = ofRandom(0.05, 0.15);
    m_rXA = ofRandom(0.05, 0.15);
    m_rYF = ofRandom(0.05, 0.15);

    m_oS = ofRandom(2*PI);
    m_oX = ofRandom(2*PI);
    m_oY = ofRandom(2*PI);
    
    m_dim = ofVec3f(ofRandom(20,60), ofRandom(10,20), ofRandom(20,60));
    m_queueLen = (int)ofRandom(60,200);
    
    setPosition(ofPoint(ofRandom(300),ofRandom(300),ofRandom(300))); //set m_matrix
    m_dim    = ofVec2f(ofRandom(20,60),ofRandom(10,20));
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
    m_dim.operator*=(getEnergy()*0.95);
    ofVec3f mat1 = ofVec3f(-m_dim.x/2,0,0);
    ofVec3f mat2 = ofVec3f(m_dim.x/2,0,0);
    ofVec3f p1 = ofVec3f(ofMap(sin(ofGetFrameNum() * m_rXF + m_oX), -m_rXA, m_rXA, -m_rXA, 200),
                          ofMap(sin(ofGetFrameNum() * m_rYF + m_oY), -m_rYA, m_rYA, -m_rYA, 200),
                          ofMap(cos(ofGetFrameNum() * m_rYF + m_oY), -m_rYA, m_rYA, -m_rYA, 200));
    
    m_queue.push_back(p1);
    //m_queue.push_back(p2);

    //Draw Vertexes
    ofBeginShape();
    for (int i = 0; i<m_queue.size();  i+=2) {
        ofVertex(m_queue[i].x, m_queue[i].y, m_queue[i].z);
    }
    ofEndShape();
    
    //limit vertices in vector object
    if(m_queue.size() > m_queueLen){
        m_queue.erase(m_queue.begin());
        m_queue.erase(m_queue.begin());
    }
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
    //m_matrix.z = speed;

}

void SnakeFish::kill()
{
    m_energy = 0.0f;
}

float SnakeFish::getEnergy()
{
    return m_energy;
}

void SnakeFish::setPosition(ofPoint pos)
{
    m_matrix = ofMatrix4x4(0, 0, 0, pos.x,
                           0, 0, 0,pos.y,
                           0, 0, 0,pos.z,
                           0, 0, 0, 0);
}
