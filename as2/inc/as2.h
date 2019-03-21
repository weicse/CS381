/*
 * as2.h
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#ifndef INC_AS2_H_
#define INC_AS2_H_

#include <EntityMgr.h>
#include "BaseApplication.h"

class As2 : public BaseApplication{
public:
	As2();
	virtual ~As2();
	virtual bool frameRenderingQueued(const Ogre::FrameEvent&);
	virtual bool keyReleased(const OIS::KeyEvent& ke);

	void generateTerrain();
	void generateEntities();
	void cameraControl(const Ogre::FrameEvent&);

	EntityMgr *entityMgr;
	Ogre::SceneNode* cameraNode;

	float speedChange;
	int surfaceHeight;
	float keyboardTimer;
	const static float keyTime = 0.1;

	virtual void createScene();
};

#endif /* INC_AS2_H_ */
