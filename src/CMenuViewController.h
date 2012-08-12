//
//  CMenuViewController.h
//  3DJ
//
//  Created by Sam Ruberti on 9/2/12.
//

#ifndef _DJ_UI_CMenuViewController_h
#define _DJ_UI_CMenuViewController_h
#include "CMenuView.h"
#include "ofxUI.h"
#include "CLoopEditorView.h"
#include "CVisualThemesView.h"
#include "CalibrationView.h"

class CMenuViewController : public ofBaseApp
{
  public:
    
    CMenuViewController(int red, int blue, int green, int alpha);
    ~CMenuViewController();

    void initViews();
    void setupDelegates();
    void menuEvent(ofxUIEventArgs &e);
    void loopEditorEvent(ofxUIEventArgs &e);
    void visualEditorEvent(ofxUIEventArgs &e);
    void showMenuView(bool _showMenuView);
    void hideAllViews();
    
    CMenuView               *m_menu;
    CLoopEditorView         *m_loopEditor;
    CVisualThemesView       *m_visualEditor;
    CalibrationView         *m_calibrationEditor;
    
    int m_r, m_g, m_b, m_a;
    bool m_exitMenu;
    
};

#endif
