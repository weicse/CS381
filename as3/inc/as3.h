/*
 * as3.h
 *
 *  Created on: Mar 1, 2019
 *      Author: wtong
 */

#ifndef INC_AS3_H_
#define INC_AS3_H_

#include <EntityMgr.h>
#include "BaseApplication.h"

class As3 : public BaseApplication{
public:
	As3();
	virtual ~As3();
	virtual bool frameRenderingQueued(const Ogre::FrameEvent&);
	virtual bool keyPressed(const OIS::KeyEvent& ke);

	void generateTerrain();
	void generateEntities();
	void cameraControl(const Ogre::FrameEvent&);

	EntityMgr *entityMgr;
	Ogre::SceneNode* cameraNode;

	int surfaceHeight;
	float deltaDesiredSpeed; //lets say the user can change the desired speed in increments/decrements of 5
	float deltaDesiredHeading;

	virtual void createScene();
};

#endif /* INC_AS3_H_ */
