#ifndef __as1_h_
#define __as1_h_

#include "BaseApplication.h"

class as1 : public BaseApplication
{
public:
	as1();
	virtual ~as1();
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	virtual bool keyReleased(const OIS::KeyEvent& ke);

	bool cameraControl(const Ogre::FrameEvent& fe);
	void positionUpdate(const Ogre::FrameEvent& fe);
	void setEnvironment();

	Ogre::SceneNode* camNode;
	Ogre::SceneNode* sphereNode;
	Ogre::Vector3 position;
	Ogre::Vector3 velocity;
	int speedChange;
	int surfaceHeight;

protected:
	virtual void createScene();
};

#endif // #ifndef __as1_h_
