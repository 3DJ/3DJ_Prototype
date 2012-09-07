//
//  CWindow_Base.h
//  3DJ
//
//  Created by Sam Ruberti on 9/1/12.
//

#ifndef _DJ_UI_CWindow_Base_h
#define _DJ_UI_CWindow_Base_h
#include "ofMain.h"
#include "ofxUI.h"

//=====================================
// Abstract Base class for all Windows
//=====================================

class CWindow_Base : public ofBaseApp 
{

public:
    
    CWindow_Base(){};
    
    virtual void setupGUI() = 0;
    virtual void saveSettings() = 0;
    virtual void loadSettings() = 0;
    virtual void showCanvases(bool show) = 0;
    virtual void setColorTheme(int theme) = 0;

    bool m_canvasesVisible;
    
};

#endif
