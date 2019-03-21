#include "as1.h"
using namespace Ogre;

as1::as1(){
	position = Vector3::ZERO;
	velocity = Vector3::ZERO;
	speedChange = 50;
	surfaceHeight = 0;
}

as1::~as1(){
}

bool as1::keyReleased(const OIS::KeyEvent& ke){

	// This function controls the velocity
	switch(ke.key){
	case OIS::KC_NUMPAD8:
		velocity.z -= speedChange;
		break;
	case OIS::KC_NUMPAD4:
		velocity.x -= speedChange;
		break;
	case OIS::KC_NUMPAD2:
		velocity.z += speedChange;
		break;
	case OIS::KC_NUMPAD6:
		velocity.x += speedChange;
		break;
	case OIS::KC_NUMPAD9:
		velocity.y += speedChange;
		break;
	case OIS::KC_NUMPAD3:
		velocity.y -= speedChange;
		break;
	case OIS::KC_SPACE:
		velocity = Vector3::ZERO;
		break;
	default:
		break;
	}
	return true;
}

void as1::createScene(){

	// Configure the lighting
	mSceneMgr->setAmbientLight(ColourValue(.5, .5, .5));
	Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(0, 200, 500);

	// Create the sphere
	// Entity* sphereEntity = mSceneMgr->createEntity("sphere.mesh");
	Entity* sphereEntity = mSceneMgr->createEntity(SceneManager::PT_SPHERE);
	sphereEntity->setMaterialName("Examples/Rockwall");
	sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("SphereNode");
	sphereNode->attachObject(sphereEntity);
	// sphereNode->showBoundingBox(true);

	// Camera node to allow custom camera keys
	camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 200, 500);
	camNode->attachObject(mCamera);

	setEnvironment();
}

bool as1::frameRenderingQueued(const FrameEvent& fe){

	// Quit when escape is pressed (also stops most key input)
	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;
	// Required for FPS and stuff to work
	mTrayMgr->frameRenderingQueued(fe);
	// Update camera movements
	cameraControl(fe);
	positionUpdate(fe);

	return true;
}

bool as1::cameraControl(const FrameEvent& fe){

	// Gotta go fast
	int move = 500;

	// Calculate direction for camera to move in
	Vector3 dirVec = Vector3::ZERO;
	if(mKeyboard->isKeyDown(OIS::KC_W))
		dirVec.z -= move;
	if(mKeyboard->isKeyDown(OIS::KC_A))
		dirVec.x -= move;
	if(mKeyboard->isKeyDown(OIS::KC_S))
		dirVec.z += move;
	if(mKeyboard->isKeyDown(OIS::KC_D))
		dirVec.x += move;
	if(mKeyboard->isKeyDown(OIS::KC_E))
		dirVec.y += move;
	if(mKeyboard->isKeyDown(OIS::KC_F))
		dirVec.y -= move;
	// Actual reposition
	camNode->translate(dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	return true;
}

void as1::positionUpdate(const FrameEvent& fe){

	// Make changes to the position
	position = position + (velocity * fe.timeSinceLastFrame);
	sphereNode->setPosition(position);
}

void as1::setEnvironment(){

	// Make the skybox
	mSceneMgr->setSkyBox(true, "Examples/StormySkyBox");

	// Create ground
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 10000, 10000, 20, 20,
		true, 1, 5, 5, 	Vector3::UNIT_Z);
	Entity* groundEntity = mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(0, surfaceHeight, 0))->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Water2");
	// groundEntity->setMaterialName("Examples/WaterStream");
	// groundEntity->setMaterialName("Ocean2_Cg");
	// groundEntity->setMaterialName("Examples/Rockwall");

	Entity* sphereAnchor1 = mSceneMgr->createEntity(SceneManager::PT_SPHERE);
	sphereAnchor1->setMaterialName("Examples/Rockwall");
	mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(500, 0, 500))->attachObject(sphereAnchor1);

	Entity* sphereAnchor2 = mSceneMgr->createEntity(SceneManager::PT_SPHERE);
	sphereAnchor2->setMaterialName("Examples/Rockwall");
	mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(-500, 0, 500))->attachObject(sphereAnchor2);

	Entity* sphereAnchor3 = mSceneMgr->createEntity(SceneManager::PT_SPHERE);
	sphereAnchor3->setMaterialName("Examples/Rockwall");
	mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(500, 0, -500))->attachObject(sphereAnchor3);

	Entity* sphereAnchor4 = mSceneMgr->createEntity(SceneManager::PT_SPHERE);
	sphereAnchor4->setMaterialName("Examples/Rockwall");
	mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(-500, 0, -500))->attachObject(sphereAnchor4);
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
	as1 app;

	try {
			app.go();
	} catch(Exception& e)	{
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
