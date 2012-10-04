//
//  BoxButton.h
//  Kinect_3DJ
//
//  Created by LJ on 9/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef Kinect_3DJ_BoxController_h
#define Kinect_3DJ_BoxController_h

#include "PointView.h"
#include "KinectData.h"
#include "DataPool.h"
#include "Interface.h"
using namespace DataPool;
using namespace Interface;

class CBoxController: public IController{
public:
    CBoxController(CDataPoolSimple* dataPool):IController(dataPool){             
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
            int index = m_dataPool->findIndexInVector( (*it) + "_centerX" );
            boxInfo.m_centerX = &(m_dataPool->getVector()[index]->second);

            index = m_dataPool->findIndexInVector((*it) + "_centerY");
            boxInfo.m_centerY = &(m_dataPool->getVector()[index]->second);

            index = m_dataPool->findIndexInVector((*it) + "_centerZ");
            boxInfo.m_centerZ = &(m_dataPool->getVector()[index]->second);

            index = m_dataPool->findIndexInVector((*it) + "_boxSize");
            boxInfo.m_boxSize = &(m_dataPool->getVector()[index]->second);

            index = m_dataPool->findIndexInVector( (*it) + "_pointsInArea");
            boxInfo.m_pointsInArea = &(m_dataPool->getVector()[index]->second);

            m_boxInfo.push_back( boxInfo );
        }
    }

    bool init();

    virtual ~CBoxController(){
        if(m_pointView) delete m_pointView;
    }

    float stringToFloat( string val )
    {
        return atof( val.c_str());
    }

    string floatToString( float f )
    {
        string str;
        str.resize(100);
        // to do: use sprintf_s.
        sprintf( (char *)str.c_str(), "%f", f );
        return str;
    }

    int stringToInt( string val)
    {
        return atoi( val.c_str());
    }

    string intToString( int i)
    {
        string str;
        str.resize(100);        
        // to do: use sprintf_s.
        sprintf( (char *)str.c_str(), "%d", i );
        return str;
    }

    struct SBoxInfo{
        string* m_centerX;
        string* m_centerY;
        string* m_centerZ;
        string* m_boxSize;
        string* m_pointsInArea;
    };
    vector<string> m_boxName;
    vector<SBoxInfo> m_boxInfo;
    CPointView * m_pointView;
    CKinectData m_oniKinect;
};

#endif
