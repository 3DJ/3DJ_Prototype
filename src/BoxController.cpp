//
//  BoxButton.h
//  Kinect_3DJ
//
//  Created by LJ on 8/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "BoxController.h"

#include "Log.h"

CBoxController::CBoxController(CDataPoolSimple* dataPool):IController(dataPool){             
    m_oniKinect.setup();
    m_pointView = new CPointView;

    m_boxName.push_back( "world_sample_a1" );
    m_boxName.push_back( "world_sample_a2" );
    m_boxName.push_back( "world_sample_a3" );
    m_boxName.push_back( "world_sample_a4" );
    m_boxName.push_back( "world_sample_b1" );
    m_boxName.push_back( "world_sample_b2" );
    m_boxName.push_back( "world_sample_b3" );
    m_boxName.push_back( "world_sample_b4" );
    m_boxName.push_back( "world_sample_c1" );
    m_boxName.push_back( "world_sample_c2" );
    m_boxName.push_back( "world_sample_c3" );
    m_boxName.push_back( "world_sample_c4" );

    for ( vector<string>::iterator it = m_boxName.begin(); it != m_boxName.end(); it++)
    {
        SBoxInfo boxInfo;        
        boxInfo.m_centerX = m_dataPool->findValueRefInVector( (*it) + "_centerX" );
        
        boxInfo.m_centerY = m_dataPool->findValueRefInVector( (*it) + "_centerY" );
        
        boxInfo.m_centerZ = m_dataPool->findValueRefInVector( (*it) + "_centerZ" );
        
        boxInfo.m_boxSize = m_dataPool->findValueRefInVector( (*it) + "_boxSize" );
        
        boxInfo.m_pointsInArea = m_dataPool->findValueRefInVector( (*it) + "_pointsInArea" );

        m_boxInfo.push_back( boxInfo );
    }
}

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
