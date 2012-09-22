//
//  CalibrationView.h
//  3DJ
//
//  Created by Samuel Ruberti on 9/19/12.
//
//

#ifndef __openNI_3DJ__CalibrationView__
#define __openNI_3DJ__CalibrationView__

#include "CWindow_Base.h"

class CalibrationView : public CWindow_Base {
    
public:
    
    CalibrationView();
    ~CalibrationView();
    
    void setupGUI();
    void setStartingValues();
    void saveSettings();
    void loadSettings();
    void showCanvases(bool show);
    void setColorTheme(int theme);
    
    ofxUICanvas *m_canvas1;
    
    float m_distThreshMin, m_distThreshMax;
    
    
    
    
};

#endif /* defined(__openNI_3DJ__CalibrationView__) */
