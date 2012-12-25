//
//  CVisualThemes.cpp
//  3DJ
//
//  Created by SamRuberti on 9/1/12.
//

#include "CVisualThemesView.h"


CVisualThemesView::CVisualThemesView(int red, int green, int blue, int alpha)
{
    m_background_r = red;
    m_background_g = green;
    m_background_b = blue;
    m_background_a = alpha;
    
    m_user_r = 220; //initial color settings for drawing of user
    m_user_g = 50;
    m_user_b = 50;
    m_user_a = 200;
    
    setupGUI(m_background_r,m_background_g,m_background_b,m_background_a);
    
}

CVisualThemesView::~CVisualThemesView()
{
    delete m_canvas1;
}

void CVisualThemesView::setupGUI()
{
    
}

void CVisualThemesView::setupGUI(int red, int green, int blue, int alpha)
{
    int dim = 16;
    int canvas_w = 320; //canvas width
    int canvas_h = ofGetScreenHeight(); //canvas height
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = canvas_w-(xInit*2);
    
    //User Drawing Styles Canvas1 =========================================================
    m_canvas1 = new ofxUICanvas(200, 0, canvas_w, canvas_h);
    
    m_canvas1->addWidgetDown(new ofxUILabel("Drawing Style", OFX_UI_FONT_LARGE));
     
    m_canvas1->addSpacer(length, 2);
    
    //Drawing Styles: ======================================================================
    vector<string> drawList; 
	drawList.push_back("Points");
	drawList.push_back("Lines");
	drawList.push_back("Avatar");
    m_canvas1->addRadio("User Style", drawList, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
    
    m_canvas1->addSpacer(length, 2);
    
    //EQWindow Settings======================================================================
    vector<string> EQList; 
    EQList.push_back("None");
	EQList.push_back("Sonic Ocean");
	EQList.push_back("Pixel Box");
    
    m_canvas1->addRadio("EQ Style", EQList, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
    
    m_canvas1->addSpacer(length, 2);

    
    //Colors for User on Screen=============================================================
    m_canvas1->addWidgetDown(new ofxUILabel("User Color",OFX_UI_FONT_MEDIUM));
    m_canvas1->addWidgetDown(new ofxUISlider("R", 0, 255, m_user_r , 300, dim,0,0));
    m_canvas1->addWidgetDown(new ofxUISlider("G", 0, 255, m_user_g , 300, dim,0,0));
    m_canvas1->addWidgetDown(new ofxUISlider("B", 0, 255, m_user_b , 300, dim,0,0));
    m_canvas1->addWidgetDown(new ofxUISlider("A", 0, 255, m_user_a , 300, dim,0,0));
    

    
    //Backgorund Color======================================================================
    m_canvas1->addWidgetDown(new ofxUILabel("Background Color",OFX_UI_FONT_MEDIUM));
    m_canvas1->addWidgetDown(new ofxUISlider("Red", 0, 255, red , 300, dim,0,0));
    m_canvas1->addWidgetDown(new ofxUISlider("Green", 0, 255, green , 300, dim,0,0));
    m_canvas1->addWidgetDown(new ofxUISlider("Blue", 0, 255, blue , 300, dim,0,0));
    m_canvas1->addWidgetDown(new ofxUISlider("Alpha", 0, 255, alpha , 300, dim,0,0));
    
}



void CVisualThemesView::saveSettings()
{
    m_canvas1->saveSettings("GUI/VisualSettings.xml");
}

void CVisualThemesView::loadSettings()
{
    m_canvas1->loadSettings("GUI/VisualSettings.xml");
}

void CVisualThemesView::showCanvases(bool show)
{
    m_canvas1->setVisible(show);
    m_canvasesVisible = show;
}

void CVisualThemesView::setColorTheme(int theme)
{
    m_canvas1->setTheme(theme);
}



