//
//  BoxButton.h
//  Kinect_3DJ
//
//  Created by LJ on 8/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "BoxController.h"

#include "Log.h"

bool CBoxController::init()
{
    m_oniKinect.update();

    ofPushMatrix();
    ofScale(-1, 1);
    ofTranslate((ofGetWidth()/2)-320, (ofGetHeight()/2) -240, -1000); // center the points a bit
    ofRotateX(180);                   //Rotate around Axis
    // ofTranslate(0,0,1000);            // Move back into Camera View
    ofTranslate(3 ,3, 3 *-800 + 1000);
    ofScale(3,3,3);

    if(m_oniKinect.m_isTracking)
    {
        int w = m_oniKinect.m_recordUser.getWidth();
        int h = m_oniKinect.m_recordUser.getHeight();

        for ( vector<SBoxInfo>::iterator it = m_boxInfo.begin(); it != m_boxInfo.end(); it++ )
        {
            int centerX = stringToInt( *(it->m_centerX));
            int centerY = stringToInt( *(it->m_centerY));
            int centerZ = stringToInt( *(it->m_centerZ));
            int size = stringToInt( *(it->m_boxSize));

            int step = 5;
            for(int y = 0; y < h; y += step) {
                for(int x = 0; x < w; x += step) {
                    ofPoint XYZ = m_oniKinect.m_recordUser.getWorldCoordinateAt(x, y, m_oniKinect.m_numberOfUsersToTrack);
                    m_pointView->addPoint(XYZ.x, XYZ.y, XYZ.z);
                    //fs<<"x:"<<XYZ.x<<"y:"<<XYZ.y<<"z:"<<XYZ.z<<endl;
                    XYZ.x = (XYZ.x - w/2) * 2;
                    XYZ.y = (XYZ.y - h/2) * 2;
                    if (XYZ.z > 0)
                    {


                        if( ((XYZ.x > centerX - size/2) && (XYZ.y > centerY - size/2) && (XYZ.z > centerZ - size))
                            &&(XYZ.x < centerX + size/2) && (XYZ.y < centerY + size/2) && (XYZ.z < centerZ + size)){
                                int pointsInArea = stringToInt( *(it->m_pointsInArea) );
                                pointsInArea++;
                                *(it->m_pointsInArea) = intToString( pointsInArea );
                        }
                    }
                }
            }
        }

        m_pointView->uploadDataToVbo();
        m_pointView->drawParticles();
        m_pointView->clearData();
    }

    ofPopMatrix();

    return true;
}
