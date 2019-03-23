/*
 * GfxMgr.cpp
 *
 *  Created on: Mar 7, 2019
 *      Author: wtong
 */

#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>

#include <Engine.h>
#include <GfxMgr.h>

GfxMgr::GfxMgr(Engine *engine) : Mgr(engine){
	// Warning if these aren't initialized
	mSceneMgr = NULL;
	mRoot = NULL;
	mCamera = NULL;
	mWindow = NULL;
}

GfxMgr::~GfxMgr(){
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	Stop();
	delete mRoot;
}

void GfxMgr::Init(){
	// Create root object
	#ifdef _DEBUG
		mResourcesCfg = "resources_d.cfg";
		mPluginsCfg = "plugins_d.cfg";
	#else
		mResourcesCfg = "resources.cfg";
		mPluginsCfg = "plugins.cfg";
	#endif

	mRoot = new Ogre::Root(mPluginsCfg);

	// Set up resources
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	Ogre::String name, locType;
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

	while (secIt.hasMoreElements()){
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;

		for (it = settings->begin(); it != settings->end(); ++it){
			locType = it->first;
			name = it->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}

	// Configure RenderSystem
	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return; // Might be good to throw an error here, if I knew how

	// Create RenderWindow
	mWindow = mRoot->initialise(true, "CS381 Assignment 5");

	// Initialize resources
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// Create a SceneManager
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

	// Create the camera
	mCamera = mSceneMgr->createCamera("MainCam");
	mCamera->setPosition(0, 0, 80);
	mCamera->lookAt(0, 0, -300);
	mCamera->setNearClipDistance(5);

	// Add a viewport
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	// Make application act as a WindowEventListener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}

bool GfxMgr::frameRenderingQueued(const Ogre::FrameEvent& fe){
	if(mWindow->isClosed())
		return false;
	return true;
	// Tutorial would return false if renderOneFrame() returned false
	// But that had to be moved down to Tick()
}


void GfxMgr::LoadLevel(){
	// Unsure what to do here
}

void GfxMgr::Stop(){
	mRoot->shutdown();
	engine->keepRunning = false;
}

void GfxMgr::Tick(float dt){
	Ogre::WindowEventUtilities::messagePump();
	mRoot->renderOneFrame(dt);
}
