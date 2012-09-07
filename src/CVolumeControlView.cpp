//
//  CVolumeControlView.cpp
//  3DJ
//
//  Created by SamRuberti on 8/30/12.
//

#include "CVolumeControlView.h"

CVolumeControlView::CVolumeControlView()
{
    setupGUI();
}

CVolumeControlView::~CVolumeControlView()
{
    delete m_canvas1;
}


void CVolumeControlView::setupGUI()
{
    m_canvas1 = new ofxUICanvas(200,0,320,ofGetScreenHeight());

    m_canvas1->addWidgetDown(new ofxUILabel("3DJ", OFX_UI_FONT_LARGE));
    m_canvas1->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0, "Master Volume"));
    
    //Box Volume control sliders
    m_canvas1->addWidgetDown(new ofxUILabel("Box Volume", OFX_UI_FONT_MEDIUM));
    m_canvas1->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0, "A1"));
    m_canvas1->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0, "A2"));
    m_canvas1->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0, "A3"));
    m_canvas1->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0, "B1"));
    m_canvas1->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0, "B2"));
    m_canvas1->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0, "B3"));
    m_canvas1->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0, "C1"));
    m_canvas1->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0, "C2"));
    m_canvas1->addWidgetDown(new ofxUISlider(304,16,0.0,100.0,100.0, "C3"));
    
}

void CVolumeControlView::saveSettings()
{
}

void CVolumeControlView::loadSettings()
{
}

void CVolumeControlView::showCanvases(bool show)
{
    m_canvas1->setVisible(show);
    m_canvasesVisible = show;
}

void CVolumeControlView::setColorTheme(int theme)
{
    m_canvas1->setTheme(theme);
}









