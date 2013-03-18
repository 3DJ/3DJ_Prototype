//
//  CBoxView.cpXYZ
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CBoxView.h"

CBoxView::CBoxView(CDataPoolSimple* dataPool): IView(dataPool)
{
    // get the objects from datapool for initializing the CBoxView
    void* temporary;
    if( dataPool->getPointerByName( "oniKinect", temporary)) {
        m_oniKinect = (CKinectData*) temporary;
    }else{
        std::cout<<"didn't get oniKinect from datapool"<<std::endl;
    }

    if( dataPool->getPointerByName( "pointView", temporary)) {
        m_pointView = (CPointView *) temporary;
    }else{
        std::cout<<"didn't get pointView from datapool"<<std::endl;
    }

    if( dataPool->getPointerByName( "easyCam", temporary)) {
        m_easyCam = (ofEasyCam *) temporary;
    }else{
        std::cout<<"didn't get easyCam from datapool"<<std::endl;
    }
    if( dataPool->getPointerByName( "equalizerView", temporary)) {
        m_equalizerView = (CEQView *) temporary;
    }else{
        std::cout<<"didn't get equalizerView from datapool"<<std::endl;
    }

    if( dataPool->getPointerByName( "snakeFish", temporary)) {
        m_snakeFish = (SnakeFish *) temporary;
    }else{
        std::cout<<"didn't get snakeFish from datapool"<<std::endl;
    }

    if( dataPool->getPointerByName( "particles", temporary)) {
        m_particles = (Particles *) temporary;
    }else{
        std::cout<<"didn't get particles from datapool"<<std::endl;
    }

    if( dataPool->getPointerByName( "a1Button", temporary)) {
        m_a1Button = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_a1Button );
    }
    if( dataPool->getPointerByName( "a2Button", temporary)) {
        m_a2Button = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_a2Button );
    }
    if( dataPool->getPointerByName( "a3Button", temporary)) {
        m_a3Button = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_a3Button );
    }
    if( dataPool->getPointerByName( "a4Button", temporary)) {
        m_a4Button = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_a4Button );
    }

    if( dataPool->getPointerByName( "b1Button", temporary)) {
        m_b1Button  = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_b1Button );
    }

    if( dataPool->getPointerByName( "b2Button", temporary)) {
        m_b2Button  = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_b2Button );
    }
    if( dataPool->getPointerByName( "b3Button", temporary)) {
        m_b3Button  = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_b3Button );
    }
    if( dataPool->getPointerByName( "b4Button", temporary)) {
        m_b4Button  = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_b4Button );
    }
    if( dataPool->getPointerByName( "controlButton_1", temporary)) {
        m_controlButton_1 = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_controlButton_1 );
    }

    if( dataPool->getPointerByName( "c1Button", temporary)) {
        m_c1Button  = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_c1Button );
    }
    if( dataPool->getPointerByName( "c2Button", temporary)) {
        m_c2Button  = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_c2Button );
    }
    if( dataPool->getPointerByName( "c3Button", temporary)) {
        m_c3Button  = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_c3Button );
    }
    if( dataPool->getPointerByName( "c4Button", temporary)) {
        m_c4Button  = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_c4Button );
    }

    m_complexor = 0;

    m_background_r = 100;
    m_background_g = 100;
    m_background_b = 100;
    m_gradientColorOutside = ofColor(24);
    m_gradientColorInside = ofColor(64);

    //Setup Scale ratio to map Kinect depth image to screen and buttons
    m_WidthScale = 1.0f;
    m_HeightScale = 1.0f;
    m_scale = scaleRatioForKinectDepthMap();
    m_playerDepth = 1000.0f;

    //SET UP BUTTONS and add all buttons to world vector============
    //    x, y, z, box size, r, g, b, a, music sample name
    //==============================================================
    m_red               = 255;
    m_green             = 255;
    m_blue              = 255;
    m_alpha             = 30;
    m_boxSize           = 225;
    m_boxCenterX        = 200;
    m_boxCenterY        = 200;
    m_boxCenterZ        = 0;
    m_controlBox_r      = 220; //control box buttons
    m_controlBox_g      = 50;
    m_controlBox_b      = 50;
    m_controlBox_a      = 30;
    float m_z = 0;

    setInitialVolume(1.0f);
    m_hands = new CHands(&CDataPoolSimple::getInstance());
    m_hands->triggerSlide();    // start tracking slide
    m_hands->triggerBoxSwitch();// start box start/shutdown switch.
    m_isRepeat      = false;
}

CBoxView::~CBoxView()
{
    if ( m_hands )
    {
        delete m_hands;
    }
}

bool CBoxView::draw()
{    
    ofBackgroundGradient(m_gradientColorInside,m_gradientColorOutside);
    m_easyCam->begin();
    ofPushMatrix();    
    ofScale(-1, 1);
    ofRotateX(180);

    // todo your render here.
    render();           // draw basic music equipments    
    m_hands->draw();    // draw hands tracking
    // end of render

    ofPopMatrix();
    m_easyCam->end();

    return true;
}

void CBoxView::render()
{           
    //setUpTranslation();             //Set up translation for all drawing

    effectBoxbutton();              // render boxbutton and handle the sound.
    if(m_oniKinect->m_isTracking){ drawDepthPoints();}   // Do both here so we only look up the m_oniKinect->data once...    

    ofPushMatrix();                 // ofPushMatrix before ofTranslate.
    ofTranslate(0, -1.5*ofGetHeight(), -5000);
    ofPopMatrix();

    //m_snakeFish->render();      //Draw Creature
    //m_snakeFish->postRender();    

    //ofPushMatrix();
    //ofTranslate(ofGetWindowWidth()/2, + ofGetWindowHeight());
    //m_particles->render();

    //ofPopMatrix();

    //    string msg = "Scale : " + ofToString(m_scale,2);
    //    ofDrawBitmapString(msg, ofGetWindowWidth()/2, ofGetWindowHeight()/2);

}

void CBoxView::drawDepthPoints()
{
    int w = m_oniKinect->m_openNIDevice.getWidth();
    int h = m_oniKinect->m_openNIDevice.getHeight();

    m_pointView->uploadDataToVbo();
    m_pointView->drawParticles();
    m_pointView->clearData();

    ofPushMatrix();
    ofTranslate(-w/2, -h/2, m_playerDepth);
    ofPopMatrix();

}


void CBoxView::addBoxButton(CBoxButton * _boxButton)
{
    m_boxButtons.push_back(_boxButton);
}

void CBoxView::handleCollisions(ofPoint *XYZ)
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->collisionTest(XYZ); //test Each Box for hits
    }
}

void CBoxView::clearButtons()
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->clear();
    }
}

void CBoxView::setInitialVolume(float volumeLevel)
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->m_soundPlayer->setVolume(volumeLevel);
    }

}

void CBoxView::setUpTranslation()
{

}

void CBoxView::effectBoxbutton()
{
    // control the slide gesture.
    static int boxOffset = 0;
    void *temp=0;
    float slideOffset = 0;
    m_dataPool->getRefByName("slideOffset", temp);

    if ( temp != 0)
    {
        slideOffset = *(float*)temp;
    }       

    if ( slideOffset != 0){
        // the boxOffset is used for sliding animation. it indicates the box screen offset, I sequently change it to make it look like a sliding.
        boxOffset = slideOffset;
    }
    else{
        if ( boxOffset >= 0 && boxOffset <= 200 ){
            // if it's not bigger than 200, I slide the box back to original
            boxOffset = boxOffset - 40;
        }
        else if( boxOffset < 0 && boxOffset >= -200 ){
            boxOffset = boxOffset + 40;
        }
        else if ( boxOffset < -200 ){
            //it it's bigger than 200, I slide the box to next group.
            boxOffset = boxOffset - 80;
        }
        else if ( boxOffset > 200 ){
            boxOffset = boxOffset + 80;
        }

    }

    if ( boxOffset > 2000 || boxOffset < -2000){
        // when the sliding is over, reload next group sounds
        reloadSounds();
        boxOffset = 0;
    }
    // end of control slide

    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++)
    {
        if ( (*eachBox)->isLoopBox() && (*eachBox)->isCurrentlyHit() )
        {// when the current hit boxButton is loop control box, open repeat switch of world.
            m_isRepeat             = true;
        }
        if ( m_isRepeat && !(*eachBox)->isLoopBox() && (*eachBox)->isCurrentlyHit() )
        {// do not repeat the control boxButton. And close the repeat switch when it touched once.
            (*eachBox)->m_isRepeat = true;
            m_isRepeat             = false;
        }

        (*eachBox)->render( boxOffset ); // Draw BoxButtons and Handle Sound.
    }
}

float CBoxView::scaleRatioForKinectDepthMap()
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


void CBoxView::reloadSounds()
{
    string songName;
    mapEntity mapSong;
    CSongs* songs = &CSongs::getInstance();
    if ( !songs->getNext(songName, mapSong)){        
        return;
    }
    cout<<"song name:"<<songName<<endl;

    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        cout<<"reload box name: "<<(*eachBox)->m_boxName<<endl;
        string soundPath = mapSong[(*eachBox)->m_boxName].value;
        cout<<"reload sound: "<<soundPath<<endl;
        (*eachBox)->reloadSound(soundPath);
    }
}
