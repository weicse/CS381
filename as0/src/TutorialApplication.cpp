// Last Modified: Wei Tong
// kojpcn@gmail.com
// February 3, 2019

#include "TutorialApplication.h"

TutorialApplication::TutorialApplication(void)
{
}

TutorialApplication::~TutorialApplication(void)
{
}

void TutorialApplication::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);
	lightNode->setPosition(20, 80, 50);

	Ogre::SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	// create the camera
	Ogre::Camera* cam = mSceneMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	camNode->setPosition(0, 47, 222);
	// and tell it to render into the main window
	// getRenderWindow()->addViewport(cam);
	// For some reason the above code doesn't work (copied straight from website tutorial)
	// However it runs just fine I think

	Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);
	ogreNode->showBoundingBox(true);

    Ogre::Entity* ogreEntity2 = mSceneMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode* ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(84, 48, 0));
    ogreNode2->attachObject(ogreEntity2);
	ogreNode2->showBoundingBox(true);
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
	// Create application object
	TutorialApplication app;

	try {
	    app.go();
	} catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	    MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
	    std::cerr << "An exception has occurred: " <<
		e.getFullDescription().c_str() << std::endl;
#endif
	}

	return 0;
    }

#ifdef __cplusplus
}
#endif
