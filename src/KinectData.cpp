//
//  CKinectData.cpp
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 8/15/12.
//
//

#include "KinectData.h"

CKinectData::CKinectData()
{
    m_dataPool = &CDataPoolSimple::getInstance();
}

void CKinectData::setup()
{
    m_dataPool->createRef( "ofxOpenNIDevice", &m_openNIDevice);
    m_isTracking	= false;
	m_isFiltering	= false;
	m_isCloud		= true;
	m_isMasking		= true;

	m_filterFactor = 0.1f;
    m_numberOfUsersToTrack = 2;// only use the depth points of the first pesron to be tracked

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
    user.setUseMaskTexture(m_isMasking);
    user.setUsePointCloud(true);
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
