//
//  CMenuView.h
//  3DJ
//
//  Created by  on 9/1/12.
//

#ifndef _DJ_UI_CMenuView_h
#define _DJ_UI_CMenuView_h
#include "CWindow_Base.h"

class CMenuView : public CWindow_Base
{    
public:
    CMenuView();
    ~CMenuView();

    void setupGUI();

    void saveSettings();
    void loadSettings();
    void setColorTheme(int theme);
    void showCanvases(bool show);
    
    ofxUICanvas *m_canvas1;

};


#endif
