//
//  CKinectData.cpp
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 8/15/12.
//
//

#include "KinectData.h"

void CKinectData::setup()
{
    m_isTracking	= false;
	m_isFiltering	= false;
	m_isCloud		= true;
	m_isMasking		= true;

	m_filterFactor = 0.1f;
    m_numberOfUsersToTrack = 1;// only use the depth points of the DJ. i.e. The first peron to be tracked

    m_openNIDevice.setup();
    m_openNIDevice.addImageGenerator();
    m_openNIDevice.addDepthGenerator();
    m_openNIDevice.setRegister(true);
    m_openNIDevice.setMirror(false);
    m_openNIDevice.addUserGenerator();
    m_openNIDevice.setMaxNumUsers(2);
    m_openNIDevice.start();
    
    // set properties for all user masks and point clouds
    //openNIDevice.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    m_openNIDevice.setUseMaskPixelsAllUsers(true);
    m_openNIDevice.setUsePointCloudsAllUsers(true);
    m_openNIDevice.setPointCloudDrawSizeAllUsers(2);
    m_openNIDevice.setPointCloudResolutionAllUsers(5);

}

void CKinectData::update()
{
    m_isTracking = true;
    m_openNIDevice.update();
}

void CKinectData::draw()
{
    

}

void CKinectData::exit()
{

}
