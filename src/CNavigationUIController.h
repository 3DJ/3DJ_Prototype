//
//  CNavigationUIController.h
//  3DJ
//
//  Created by Samuel Ruberti on 9/22/12.
//
//

#ifndef __openNI_3DJ__CNavigationUIController__
#define __openNI_3DJ__CNavigationUIController__
#include "ofMain.h"
#include "CNavigationControlButtons.h"

class CNavigationUIController: public ofBaseApp  {
    
public:
    
    CNavigationUIController();
    ~CNavigationUIController();
   
    CNavigationControlButtons *m_navConButtons;
    
};

#endif /* defined(__openNI_3DJ__CNavigationUIController__) */
