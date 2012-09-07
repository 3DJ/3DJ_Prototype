//
//  CVolumeControlView.h
//  3DJ
//
//  Created by Sam Ruberti on 8/30/12.
//

#ifndef _DJ_UI_CVolumeControlView_h
#define _DJ_UI_CVolumeControlView_h

#include "ofxUI.h"
#include "CWindow_Base.h"

class CVolumeControlView : public CWindow_Base
{

public:

    CVolumeControlView();
    ~CVolumeControlView();
    
    void setupGUI();
    void saveSettings();
    void loadSettings();
    void setColorTheme(int theme);
    void showCanvases(bool show);
    
    ofxUICanvas *m_canvas1;
    
};

#endif
