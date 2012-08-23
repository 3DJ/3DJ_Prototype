//
//  CPointView.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_PointView_h
#define Kinect_3DJ_PointView_h
#include "ofMain.h"

class CPointView : public ofBaseApp
{
public:
    CPointView();
    ~CPointView();

    void drawParticles();
    void addPoint( const float x, const float y, const float z);
    void clearData();
    void uploadDataToVbo();

private:
    vector <ofVec3f> m_points;
    vector <ofVec3f> m_sizes;

    ofVbo m_vbo;
    ofShader m_shader;
    ofTexture m_texture;
};

#endif
