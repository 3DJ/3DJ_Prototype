//
//  CVisualThemesView.h
//  3DJ
//
//  Created by Sam Ruberti on 9/1/12.
//

#ifndef _DJ_UI_CVisualThemesView_h
#define _DJ_UI_CVisualThemesView_h
#include "CWindow_Base.h"

class CVisualThemesView : public CWindow_Base
{
    
public:
    CVisualThemesView(int red, int green, int blue, int alpha);
    ~CVisualThemesView();
    
    void setupGUI();
    void setupGUI(int red, int green, int blue, int alpha);
    void saveSettings();
    void loadSettings();
    void showCanvases(bool show);
    void setColorTheme(int theme);
    
    ofxUICanvas *m_canvas1;  
    ofxUICanvas *m_canvas2;
    
    int m_background_r,m_background_g,m_background_b,m_background_a; //RGBA values for background color
    int m_user_r, m_user_g, m_user_b, m_user_a; //RGBA values for user on screen
    
    
};

#endif
