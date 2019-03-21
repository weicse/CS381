/*
 * GfxMgr.h
 *
 *  Created on: Mar 7, 2019
 *      Author: wtong
 */

#ifndef INC_GFXMGR_H_
#define INC_GFXMGR_H_

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include <Mgr.h>

class GfxMgr : public Mgr, public Ogre::WindowEventListener, public Ogre::FrameListener{
public:
	GfxMgr(Engine *);
	virtual ~GfxMgr();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();

	// Tutorial 6 objects
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
};

#endif /* INC_GFXMGR_H_ */
