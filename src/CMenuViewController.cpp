//
//  CMenuViewController.cpp
//  3DJ
//
//  Created by Sam Ruberti on 9/2/12.
//

#include "CMenuViewController.h"


CMenuViewController::CMenuViewController(int red, int green, int blue, int alpha)
{
    m_r = red;
    m_g = green;
    m_b = blue;
    m_a = alpha;
    m_exitMenu = false;
    
    initViews();
    setupDelegates(); //adds ofAddListener for each ofxUICanvas in views
    hideAllViews(); //hide all views at start
    showMenuView(true); //Start with menu
}

CMenuViewController::~CMenuViewController()
{
    delete m_menu;
    delete m_volumeEditor;
    delete m_loopEditor;
    delete m_visualEditor;
}

void CMenuViewController::initViews()
{
    m_menu = new CMenuView;
    m_volumeEditor = new CVolumeControlView();
    m_loopEditor = new CLoopEditorView();
    m_visualEditor = new CVisualThemesView(m_r, m_g, m_b, m_a);
}

void CMenuViewController::menuEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    if(name == "Box Volume"){
        m_volumeEditor->m_canvas1->setVisible(true);
        m_loopEditor->m_canvas1->setVisible(false);
        m_visualEditor->m_canvas1->setVisible(false);
    }else if(name == "Drawing Style"){
        m_volumeEditor->m_canvas1->setVisible(false);
        m_loopEditor->m_canvas1->setVisible(false);
        m_visualEditor->m_canvas1->setVisible(true);
    }else if(name == "Start Session"){
        m_exitMenu = true;
        hideAllViews();
    }else if(name == "Loop Editor"){
        m_volumeEditor->m_canvas1->setVisible(false);
        m_loopEditor->m_canvas1->setVisible(true);
        m_visualEditor->m_canvas1->setVisible(false);
    }else if(name == "Sound Effects"){                  //Add sound effect editor
        m_volumeEditor->m_canvas1->setVisible(false);
        m_loopEditor->m_canvas1->setVisible(false);
        m_visualEditor->m_canvas1->setVisible(false);
    }else if(name == "Calibrate"){                      //Add calibration editor
        m_volumeEditor->m_canvas1->setVisible(false);
        m_loopEditor->m_canvas1->setVisible(false);
        m_visualEditor->m_canvas1->setVisible(false);
    }else if(name == "About 3DJ"){                      //Add calibration editor
        m_volumeEditor->m_canvas1->setVisible(false);
        m_loopEditor->m_canvas1->setVisible(false);
        m_visualEditor->m_canvas1->setVisible(false);
    }
}

void CMenuViewController::volumeEditorEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    
    if(name == ""){

    }else if(name == ""){
        
    }
}

void CMenuViewController::loopEditorEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    
    if(name == ""){

    }else if(name == ""){
        
    }
}

void CMenuViewController::visualEditorEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    
    if(name == "Fullscreen"){
        ofToggleFullscreen();
    }else if(name == ""){
        
    }
}

void CMenuViewController::setupDelegates()
{
    ofAddListener(m_menu->m_canvas1->newGUIEvent, this, &CMenuViewController::menuEvent);
    ofAddListener(m_volumeEditor->m_canvas1->newGUIEvent, this, &CMenuViewController::volumeEditorEvent);
    ofAddListener(m_loopEditor->m_canvas1->newGUIEvent, this, &CMenuViewController::loopEditorEvent);
    ofAddListener(m_visualEditor->m_canvas1->newGUIEvent, this, &CMenuViewController::visualEditorEvent);
   
}

void CMenuViewController::showMenuView(bool _showMenuView)
{
    if(_showMenuView){
        m_menu->m_canvas1->setVisible(_showMenuView);
    }else {
        //hideallViews();
    }
}

void CMenuViewController::hideAllViews()
{
    m_menu->m_canvas1->setVisible(false);
    m_loopEditor->m_canvas1->setVisible(false);
    m_visualEditor->m_canvas1->setVisible(false);
    m_volumeEditor->m_canvas1->setVisible(false);
}



