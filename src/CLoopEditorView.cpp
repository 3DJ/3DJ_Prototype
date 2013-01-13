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
    delete m_canvas2;
}

void CLoopEditorView::setupGUI()
{
    ofColor paddingColor = ofColor(152,202,86,200);
    int dim = 16;
    int xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    int widthOffset = 200;
    int heightOffset = 50;
    int canvasOneWidth = (ofGetScreenWidth()-widthOffset) / 2;
    int canvasOneHeight = ofGetScreenHeight();

    int canvasTwoWidth = (ofGetScreenWidth()-widthOffset) / 2;
    int canvasTwoHeight = ofGetScreenHeight()-heightOffset;
    
    int spacerHeight = 15;
    
    int buttonHeight = 48;
    int buttonWidth  = 96;
    
    
    //Canvas One ------------------
    m_canvas1 = new ofxUICanvas(widthOffset,heightOffset,canvasOneWidth,canvasOneHeight);

    m_canvas1->addWidgetDown(new ofxUILabel("Loop Editor",OFX_UI_FONT_LARGE));
    m_canvas1->addWidgetDown(new ofxUILabel("Audio Player",OFX_UI_FONT_MEDIUM));
    m_canvas1->addWidgetDown(new ofxUIToggleMatrix(dim*8.0, dim*8.0, 3, 4, "Matrix A"));
    
    
    // Canvas Two -----------------
    m_canvas2 = new ofxUICanvas(widthOffset + canvasOneWidth,heightOffset,canvasTwoWidth,canvasTwoHeight);
    m_canvas2->setDrawBack(false);
    
    m_canvas2->addWidgetDown(new ofxUILabel("Audio Loader",OFX_UI_FONT_LARGE));
    
	ofxUIWidget *w = (ofxUILabel *) m_canvas2->addWidgetDown(new ofxUILabel(canvasTwoWidth - xInit, "Click on Button to Load File", OFX_UI_FONT_LARGE));
    w->setColorPadded(paddingColor);
    
    //Loop Loader Row A
    vector<string> boxRowA;
	boxRowA.push_back("A1");
	boxRowA.push_back("A2");
	boxRowA.push_back("A3");
    boxRowA.push_back("A4");
    w = m_canvas2->addRadio("Row A", boxRowA, OFX_UI_ORIENTATION_HORIZONTAL, dim*3, dim*3);
    w->setColorPadded(paddingColor);

    //Loop Loader Row B
    vector<string> boxRowB;
	boxRowB.push_back("B1");
	boxRowB.push_back("B2");
	boxRowB.push_back("B3");
    boxRowB.push_back("B4");
    w = m_canvas2->addRadio("Row B", boxRowB, OFX_UI_ORIENTATION_HORIZONTAL, dim*3, dim*3);
    w->setColorPadded(paddingColor);
    
    //Loop Loader Row C
    vector<string> boxRowC;
	boxRowC.push_back("C1");
	boxRowC.push_back("C2");
	boxRowC.push_back("C3");
    boxRowC.push_back("C4");
    w = m_canvas2->addRadio("Row C", boxRowC, OFX_UI_ORIENTATION_HORIZONTAL, dim*3, dim*3);
    w->setColorPadded(paddingColor);
    
    m_canvas1->setDrawWidgetPadding(false);
    m_canvas2->setDrawWidgetPadding(false);

}

void CLoopEditorView::saveSettings()
{
    m_canvas1->saveSettings("GUI/LoopEditorSettings.xml");
    m_canvas2->saveSettings("GUI/LoopEditorSettings.xml");
}

void CLoopEditorView::loadSettings()
{
    m_canvas1->loadSettings("GUI/LoopEditorSettings.xml");
    m_canvas2->loadSettings("GUI/LoopEditorSettings.xml");
}

void CLoopEditorView::showCanvases(bool show)
{
    m_canvas1->setVisible(show);
    m_canvas2->setVisible(show);
    m_canvasesVisible = show;
}

void CLoopEditorView::setColorTheme(int theme)
{
    m_canvas1->setTheme(theme);
    m_canvas2->setTheme(theme);
}
