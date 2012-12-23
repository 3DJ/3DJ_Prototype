//
//  CLoopEditorView.cpp
//  3DJ
//
//  Created by Sam Ruberti on 9/1/12.
//

#include "CLoopEditorView.h"

CLoopEditorView::CLoopEditorView()
{
    setupGUI();
}

CLoopEditorView::~CLoopEditorView()
{
    saveSettings();
    delete m_canvas1;
}

void CLoopEditorView::setupGUI()
{
    int dim = 16;
    
    int widthOffset = 200;
    int canvasOneWidth = ofGetScreenWidth()-widthOffset;
    int canvasOneHeight = ofGetScreenHeight();
    
    
    //Track1
    m_canvas1 = new ofxUICanvas(widthOffset,0,canvasOneWidth,canvasOneHeight);

    m_canvas1->addWidgetDown(new ofxUILabel("Loop Editor",OFX_UI_FONT_MEDIUM));
    m_canvas1->addWidgetDown(new ofxUILabel("Box A-1",OFX_UI_FONT_SMALL));
    m_canvas1->addWidgetDown(new ofxUISlider("Track Volume", 0, 100.0, 100, 200, dim));
    m_canvas1->addWidgetRight(new ofxUIRangeSlider("Start/End", 0, 100, 0, 100,ofGetScreenWidth()*0.6 , dim));
    m_canvas1->addWidgetDown(new ofxUIImageButton(0, 0, dim*2, dim*2, false, "icons/play.png", "Play"));
    m_canvas1->addWidgetRight(new ofxUIImageButton(0, 0, dim*2, dim*2, true, "icons/pause.png", "Pause"));
    m_canvas1->addWidgetRight(new ofxUIImageButton(0, 0, dim*2, dim*2, false, "icons/loadFile.png", "Load"));
    m_canvas1->addWidgetRight(new ofxUIImageButton(0, 0, dim*2, dim*2, false, "icons/saveFile.png", "Save Settings"));

}

void CLoopEditorView::saveSettings()
{
    m_canvas1->saveSettings("GUI/LoopEditorSettings.xml");
}

void CLoopEditorView::loadSettings()
{
    m_canvas1->loadSettings("GUI/LoopEditorSettings.xml");
}

void CLoopEditorView::showCanvases(bool show)
{
    m_canvas1->setVisible(show);
    m_canvasesVisible = show;
    
}

void CLoopEditorView::setColorTheme(int theme)
{
    m_canvas1->setTheme(theme);
}