//
//  CNavigationUIController.cpp
//  3DJ
//
//  Created by Samuel Ruberti on 9/22/12.
//
//

#include "CNavigationUIController.h"


CNavigationUIController::CNavigationUIController()
{
    m_navConButtons = new CNavigationControlButtons("Cham Culture");
}

CNavigationUIController::~CNavigationUIController()
{
    if (m_navConButtons) delete m_navConButtons;
}



