//
//  CalibrationView.cpp
//  3DJ
//
//  Created by Samuel Ruberti on 9/19/12.
//
//

#include "CalibrationView.h"

CalibrationView::CalibrationView(){
    setStartingValues();
    setupGUI();
}

CalibrationView::~CalibrationView(){
    saveSettings();
    delete m_canvas1;
}

void CalibrationView::setupGUI(){
    int dim = 16;
    int canvas_w = 200; //canvas width
    int canvas_h = ofGetScreenHeight(); //canvas height
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = canvas_w-(xInit*2);
    
    m_canvas1 = new ofxUICanvas(200, 0, canvas_w, ofGetScreenHeight());
                                
    m_canvas1->addWidgetDown(new ofxUILabel("Calibration",OFX_UI_FONT_LARGE));
    m_canvas1->addSpacer(length, 2);
    
    vector<string> numberOfUsersList;
    numberOfUsersList.push_back("All Objects");
    numberOfUsersList.push_back("1");
    numberOfUsersList.push_back("2");
    numberOfUsersList.push_back("3");
    
    m_canvas1->addWidgetDown(new ofxUIRadio("Number of Users", numberOfUsersList, OFX_UI_ORIENTATION_VERTICAL, dim, dim));
    
    m_canvas1->addSpacer(length, 2);
    
    m_canvas1->addWidgetDown(new ofxUILabel("Distance Threshold",OFX_UI_FONT_MEDIUM));
    
    m_canvas1->addWidgetDown(new ofxUIRangeSlider("Min/Max (meters)", 1.0f, 27.0f, &m_distThreshMin, &m_distThreshMax, length, dim));
}

void CalibrationView::setStartingValues(){
    m_distThreshMax = 12.0f;
    m_distThreshMin = 2.0f;
}

void CalibrationView::saveSettings(){
    
}

void CalibrationView::loadSettings(){
    
}

void CalibrationView::showCanvases(bool show){
    m_canvas1->setVisible(show);
    m_canvasesVisible = show;
}

void CalibrationView::setColorTheme(int theme){
    m_canvas1->setTheme(theme);
}