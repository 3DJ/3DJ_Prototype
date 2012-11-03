//
//  NavigationUIView.h
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 9/22/12.
//
//

#ifndef __openNI_3DJ__NavigationUIView__
#define __openNI_3DJ__NavigationUIView__
#include "Entity.h"

class NavigationUIView : public CNavigationUIBase {
    NavigationUIView();
    ~NavigationUIView();
    
    
    
    void circleStroke( int _center_x, int _center_y, int _radius, int _strokeWidth, float _startAngle, float _endAngle, int _circleResolution );




};

#endif /* defined(__openNI_3DJ__NavigationUIView__) */
