//
//  CNavigationControlButtons.h
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 9/22/12.
//
//

#ifndef __openNI_3DJ__CNavigationControlButtons__
#define __openNI_3DJ__CNavigationControlButtons__
#include "Entity.h"

class CNavigationControlButtons: public CControlButtonsBase {
public:
    
    CNavigationControlButtons();
    CNavigationControlButtons(string test);
    ~CNavigationControlButtons();
    
    void render();
    void update(double time_since_last_update);
    void setupVariables();
    void drawCircleStroke();
    bool collisionTest(ofPoint *point);
    void windowSizeChanged();
    
    bool m_active;
    
    float m_x, m_y, m_z; //location
    float m_r, m_g, m_b, m_a; //color
    float m_total_time; //time elapsed since creation
    
    int m_resolution, m_strokeWidth, m_radius;
    float m_startAngle, m_endAngle;
    
    EntityType m_type;
};

#endif /* defined(__openNI_3DJ__CNavigationControlButtons__) */
