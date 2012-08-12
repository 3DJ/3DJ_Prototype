//
//  CPointView.cpp
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PointView.h"

CPointView::CPointView()
{
    ofDisableArbTex();
    ofLoadImage(m_texture, "dot.png");
    m_shader.load("shader");
}
CPointView::~CPointView()
{

}

void CPointView:: drawParticles()
{
    ofPushMatrix();
    ofSetColor(50, 100, 5, 40);
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnablePointSprites();

    m_shader.begin();

    m_texture.bind();
    m_vbo.draw(GL_POINTS, 0, (int)m_points.size());
    m_texture.unbind();
    m_shader.end();

    ofDisablePointSprites();
    ofDisableBlendMode();
    ofDisableAlphaBlending();

    ofPopMatrix();   
}

void CPointView::addPoint( const float x, const float y, const float z)
{
    ofVec3f p(x,y,z);
    m_points.push_back(p);

    //Pass the size in as a normal x position
    float size = ofRandom(25,50);
    m_sizes.push_back(size);
}

void CPointView::clearData()
{
    m_points.clear(); //clear point data
    m_sizes.clear();
    m_vbo.clear();
}

void CPointView::uploadDataToVbo()
{
    m_vbo.setVertexData(&m_points[0], (int)m_points.size(), GL_STATIC_DRAW);
    m_vbo.setNormalData(&m_sizes[0],(int)m_sizes.size(), GL_STATIC_DRAW);
}