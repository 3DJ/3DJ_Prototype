//
//  CKinectData.h
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 8/15/12.
//
//

#ifndef __openNI_3DJ__KinectData__
#define __openNI_3DJ__KinectData__

#include <iostream>
#include "ofxOpenNI.h"

class CKinectData {
public:
    
    void setup();
	void update();
    void draw();

    bool m_isTracking, m_isCloud, m_isMasking, m_isFiltering;
    
    float				m_filterFactor;
    int                 m_numberOfUsersToTrack;

    ofxOpenNIContext	m_recordContext;
	ofxDepthGenerator	m_recordDepth;
	ofxUserGenerator	m_recordUser;
    
};




#endif /* defined(__openNI_3DJ__KinectData__) */
