//
//  CLoopEditorView.h
//  3DJ
//
//  Created by  on 9/1/12.
//

#ifndef _DJ_UI_CLoopEditorView_h
#define _DJ_UI_CLoopEditorView_h
#include "CWindow_Base.h"

class CLoopEditorView : public CWindow_Base
{
    
public:
        
    CLoopEditorView();
    ~CLoopEditorView();
    
    void setupGUI();
    void saveSettings();
    void loadSettings();
    void showCanvases(bool show);
    void setColorTheme(int theme);
    
    ofxUICanvas *m_canvas1;    
    
};

#endif
