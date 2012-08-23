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
    m_isTracking		= true;
	m_isFiltering		= false;
	m_isCloud			= true;
	m_isCPBkgnd		= true;
	m_isMasking		= true;

	m_filterFactor = 0.1f;
    m_numberOfUsersToTrack = 1;// only use the depth points of the DJ. i.e. The first peron to be tracked

    m_recordContext.setup();

    m_recordDepth.setup(&m_recordContext);
    m_recordUser.setup(&m_recordContext);

    m_recordUser.setSmoothing(m_filterFactor);	// built in openni skeleton smoothing...
    m_recordUser.setUseMaskPixels(m_isMasking);

    m_recordUser.setUseCloudPoints(m_isCloud);
    m_recordUser.setMaxNumberOfUsers(2);	// use this to set dynamic max number of users

}

void CKinectData::update()
{
    if (m_isTracking)
    {
        m_recordContext.update();
        m_recordUser.update();
    }
}

void CKinectData::draw()
{
    //m_recordUser.draw(); //Dot in upper left hand corner. Green = tracking User, Red != tracking
}
