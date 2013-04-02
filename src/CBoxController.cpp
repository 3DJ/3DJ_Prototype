//
//  CBoxController.cpXYZ
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CBoxController.h"

CBoxController::CBoxController()
{  
    //Set up Kinect
    m_oniKinect.setup();

    m_background_r = 100;
    m_background_g = 100;
    m_background_b = 100;
    m_gradientColorOutside = ofColor(24);
    m_gradientColorInside = ofColor(64);

    //Setup Scale ratio to map Kinect depth image to screen and buttons
    m_WidthScale = 1.0f;
    m_HeightScale = 1.0f;
    m_scale = scaleRatioForKinectDepthMap();
    m_playerDepth = 1200.0f;

    //SET UP BUTTONS and add all buttons to world vector============
    //    x, y, z, box size, r, g, b, a, music sample name
    //==============================================================
    m_red               = 255;
    m_green             = 255;
    m_blue              = 255;
    m_alpha             = 30;
    m_boxSize           = 200;
    m_boxCenterX        = 200;
    m_boxCenterY        = 200;
    m_boxCenterZ        = 0;
    m_controlBox_r      = 220; //control box buttons
    m_controlBox_g      = 50;
    m_controlBox_b      = 50;
    m_controlBox_a      = 30;

    float m_z = 0;
    float rotation      = -15.0f; //rotation for boxes
    int x1 = 550;
    int x2 = 250;
    int z1 = 150;     //150 is decent
    int z2 = 0;
    int y1 = 270;

    string songName;
    mapEntity mapSong;
    CSongs* songs = &CSongs::getInstance();
    if ( !songs->getFirst(songName, mapSong)){
        ofLogVerbose("there is no song bundle in songs folder");
        return;
    }

    //Loop Button
    m_controlButton_1 = new CLoopBoxButton("loop", 0, y1, -z2*0.5, m_boxSize*.85,m_controlBox_r,m_controlBox_g,m_controlBox_b,m_controlBox_a,"",0);
    addBoxButton(m_controlButton_1);
    //Row A
    string soundPath = mapSong["A1"].value;
    if ( m_dataPool->findValueRef( "A1"))
    {
        m_dataPool->getValueByName( "A1", soundPath);
    }

    m_a1Button = new CBoxButton("A1", x1, -y1, z1, m_boxSize,m_red,m_green,m_blue,m_alpha,soundPath, rotation);
    addBoxButton(m_a1Button);

    soundPath = mapSong["A2"].value;
    if ( m_dataPool->findValueRef( "A2"))
    {
        m_dataPool->getValueByName( "A2", soundPath);
    }
    m_a2Button = new CBoxButton("A2", x2, -y1, z2, m_boxSize,m_red,m_green,m_blue,m_alpha,soundPath, rotation);
    addBoxButton(m_a2Button);

    soundPath = mapSong["A3"].value;
    if ( m_dataPool->findValueRef( "A3"))
    {
        m_dataPool->getValueByName( "A3", soundPath);
    }
    m_a3Button = new CBoxButton("A3", -x2,-y1,z2, m_boxSize,m_red,m_green,m_blue,m_alpha,soundPath, -rotation);
    addBoxButton(m_a3Button);

    soundPath = mapSong["A4"].value;
    if ( m_dataPool->findValueRef( "A4"))
    {
        m_dataPool->getValueByName( "A4", soundPath);
    }
    m_a4Button = new CBoxButton("A4", -x1, -y1, z1, m_boxSize, m_red,m_green,m_blue,m_alpha,soundPath, -rotation);
    m_a4Button->m_soundPlayer->setVolume(0.60f);
    addBoxButton(m_a4Button);

    //Row B
    soundPath = mapSong["B1"].value;
    if ( m_dataPool->findValueRef( "B1"))
    {
        m_dataPool->getValueByName( "B1", soundPath);
    }
    m_b1Button = new CBoxButton("B1", x1, 0, z1, m_boxSize,m_red,m_green,m_blue,m_alpha,soundPath, rotation);
    addBoxButton(m_b1Button);

    soundPath = mapSong["B2"].value;
    if ( m_dataPool->findValueRef( "B2"))
    {
        m_dataPool->getValueByName( "B2", soundPath);
    }
    m_b2Button = new CBoxButton("B2", x2, 0, z2, m_boxSize,m_red,m_green,m_blue,m_alpha,soundPath, rotation);
    addBoxButton(m_b2Button);

    soundPath = mapSong["B3"].value;
    if ( m_dataPool->findValueRef( "B3"))
    {
        m_dataPool->getValueByName( "B3", soundPath);
    }
    m_b3Button = new CBoxButton("B3", -x2, 0, z2, m_boxSize,m_red,m_green,m_blue,m_alpha,soundPath, -rotation);
    addBoxButton(m_b3Button);

    soundPath = mapSong["B4"].value;
    if ( m_dataPool->findValueRef( "B4"))
    {
        m_dataPool->getValueByName( "B4", soundPath);
    }
    m_b4Button = new CBoxButton("B4", -x1,0, z1, m_boxSize,m_red,m_green,m_blue,m_alpha, soundPath, -rotation);
    addBoxButton(m_b4Button);

    //Row C
    soundPath = mapSong["C1"].value;
    if ( m_dataPool->findValueRef( "C1"))
    {
        m_dataPool->getValueByName( "C1", soundPath);
    }
    m_c1Button = new CBoxButton("C1", x1, y1, z1, m_boxSize,m_red,m_green,m_blue,m_alpha,soundPath, rotation);
    addBoxButton(m_c1Button);

    soundPath = mapSong["C2"].value;
    if ( m_dataPool->findValueRef( "C2"))
    {
        m_dataPool->getValueByName( "C2", soundPath);
    }
    m_c2Button = new CBoxButton("C2", x2, y1, z2, m_boxSize, m_red,m_green,m_blue,m_alpha,soundPath, rotation);
    addBoxButton(m_c2Button);

    soundPath = mapSong["C3"].value;
    if ( m_dataPool->findValueRef( "C3"))
    {
        m_dataPool->getValueByName( "C3", soundPath);
    }
    m_c3Button = new CBoxButton("C3", -x2, y1, z2, m_boxSize,m_red,m_green,m_blue,m_alpha,soundPath, -rotation);
    addBoxButton(m_c3Button);

    soundPath = mapSong["C4"].value;
    if ( m_dataPool->findValueRef( "C4"))
    {
        m_dataPool->getValueByName( "C4", soundPath);
    }
    m_c4Button = new CBoxButton("C4", -x1, y1, z1, m_boxSize,m_red,m_green,m_blue,m_alpha,soundPath, -rotation);
    addBoxButton(m_c4Button);

    setInitialVolume(1.0f);

    m_pointView     = new CPointView();
    m_easyCam       = new ofEasyCam;

    m_equalizerView = new CEQView;

    m_isRepeat      = false;

    m_snakeFish = new SnakeFish();
    m_particles = new Particles();

    m_dataPool->createRef( "oniKinect", (void*)&m_oniKinect );
    m_dataPool->createRef( "pointView", (void*)m_pointView);
    m_dataPool->createRef( "easyCam", (void*)m_easyCam);
    m_dataPool->createRef( "equalizerView", (void*)m_equalizerView );
    m_dataPool->createRef( "snakeFish", (void*)m_snakeFish);
    m_dataPool->createRef( "particles", (void*)m_particles);

    //
    m_dataPool->createRef("boxButtons", (void*)&m_boxButtons);
//     m_dataPool->createRef( "a1Button", (void*)m_a1Button);
//     m_dataPool->createRef( "a2Button", (void*)m_a2Button);
//     m_dataPool->createRef( "a3Button", (void*)m_a3Button);
//     m_dataPool->createRef( "a4Button", (void*)m_a4Button);
// 
//     m_dataPool->createRef( "b1Button", (void*)m_b1Button);
//     m_dataPool->createRef( "b2Button", (void*)m_b2Button);
//     m_dataPool->createRef( "b3Button", (void*)m_b3Button);
//     m_dataPool->createRef( "b4Button", (void*)m_b4Button);
//     m_dataPool->createRef( "controlButton_1", (void*)m_controlButton_1);
// 
//     m_dataPool->createRef( "c1Button", (void*)m_c1Button);
//     m_dataPool->createRef( "c2Button", (void*)m_c2Button);
//     m_dataPool->createRef( "c3Button", (void*)m_c3Button);
//     m_dataPool->createRef( "c4Button", (void*)m_c4Button);
}

CBoxController::~CBoxController()
{
    m_oniKinect.exit();

    for( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++)
    {
        delete (*eachBox);
    }

    if(m_pointView) delete m_pointView;
    if(m_easyCam) delete m_easyCam;
    if(m_equalizerView) delete m_equalizerView;
    if(m_snakeFish) delete m_snakeFish;
    if(m_particles) delete m_particles;
}

bool CBoxController::update()
{
    update(ofGetElapsedTimef());
    testHits();

    return true;
}

void CBoxController::update(double time_since_last_update)
{

    m_oniKinect.update();
    m_equalizerView->soundUpdate();
    m_snakeFish->preRender();
    m_snakeFish->move();
    m_particles->update();

}

void CBoxController::testHits()
{
    int w = m_oniKinect.m_openNIDevice.getWidth();
    int h = m_oniKinect.m_openNIDevice.getHeight();
    int numUsers = m_oniKinect.m_openNIDevice.getNumTrackedUsers();
    int step = 1;

    for (int i = 0; i < numUsers; i++) {

        ofxOpenNIUser & user = m_oniKinect.m_openNIDevice.getTrackedUser(i);

        ofMesh userMesh = user.getPointCloud();
        vector<ofVec3f> vertices =  userMesh.getVertices();
        for (vector<ofVec3f>::iterator vertex = vertices.begin(); vertex < vertices.end(); vertex+=step) {

            ofPoint XYZ = ofPoint(vertex->x,vertex->y,vertex->z);
            if (XYZ.z > 0) {
                XYZ.x = (XYZ.x - w/2)*m_scale;
                XYZ.y = (XYZ.y - h/2)*m_scale;
                XYZ.z -= m_playerDepth;

                checkBoxHits(XYZ);      // check the box hits
                m_pointView->addPoint(XYZ.x, XYZ.y, XYZ.z);// draw the avatar by cloud points
            }
        }
    }

    ofPushMatrix();
    ofTranslate(-w/2, -h/2, m_playerDepth);
    ofPopMatrix();
}

void CBoxController::addBoxButton(CBoxButton * _boxButton)
{
    m_boxButtons.push_back(_boxButton);
}

void CBoxController::handleCollisions(ofPoint *XYZ)
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {//test Each Box for hits        
        if ((*eachBox)->collisionTest(XYZ)){
            return;
        } 
    }
}

void CBoxController::clearButtons()
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->clear();
    }
}

void CBoxController::setInitialVolume(float volumeLevel)
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->m_soundPlayer->setVolume(volumeLevel);
    }

}

float CBoxController::scaleRatioForKinectDepthMap()
{
    float w = 640.0f;
    float h = 480.0f;
    float screenW = float(ofGetScreenWidth());
    float screenH = float(ofGetScreenHeight());

    if((w/h) < (screenW/screenH)){
        return screenW/w;
    }else {
        return screenH/h;
    }
}

void CBoxController::checkBoxHits( ofPoint XYZ )
{
    handleCollisions(&XYZ); //check for hits for all buttons               
    /* the code below is for startup gesture.
    void *temp = 0;
    bool isBoxStartedUp;
    m_dataPool->getRefByName("isBoxStartedUp", temp);
    if ( temp != 0 )
    {
        isBoxStartedUp = *(bool *)temp;
        if ( isBoxStartedUp )
        {
            handleCollisions(&XYZ); //check for hits for all buttons                
        }                                       
    }
    */
}
