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
	m_isMasking		= false;

	m_filterFactor = 0.1f;
    m_numberOfUsersToTrack = 1;// only use the depth points of the DJ. i.e. The first peron to be tracked

    m_openNIDevice.setup();
    m_openNIDevice.addImageGenerator();
    m_openNIDevice.addDepthGenerator();
    m_openNIDevice.setRegister(true);
    m_openNIDevice.setMirror(false);
    m_openNIDevice.addUserGenerator();
    m_openNIDevice.setMaxNumUsers(m_numberOfUsersToTrack);
    m_openNIDevice.setUsePointCloudsAllUsers(m_isCloud);
    m_openNIDevice.start();
    
    /*Setup Base User Settings */
    ofxOpenNIUser user;
    user.setUseMaskTexture(true);
    user.setUsePointCloud(true);
    user.setPointCloudDrawSize(2); // this is the size of the glPoint that will be drawn for the point cloud
    user.setPointCloudResolution(5); // this is the step size between points for the cloud
    m_openNIDevice.setBaseUserClass(user);
    
}

void CKinectData::update()
{
    m_isTracking = m_openNIDevice.getNumTrackedUsers() > 0;
    m_openNIDevice.update();
}

void CKinectData::draw()
{


}

void CKinectData::exit()
{
    
}
