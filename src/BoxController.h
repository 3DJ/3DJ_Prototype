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
#include "Common.h"
using namespace DataPool;
using namespace Interface;
using namespace Common;

class CBoxController: public IController{
public:
    CBoxController(CDataPoolSimple* dataPool);

    bool init();

    virtual ~CBoxController(){
        if(m_pointView) delete m_pointView;
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
