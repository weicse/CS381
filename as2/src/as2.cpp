/*
 * as2.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#include <as2.h>
using namespace Ogre;

As2::As2(void){
	speedChange = 50;
	surfaceHeight = 0;
	keyboardTimer = keyTime;
	cameraNode = 0;
	entityMgr = 0;
}

As2::~As2(void){
}

void As2::createScene(void){

	// Configure the lighting
	mSceneMgr->setAmbientLight(ColourValue(.5, .5, .5));
	Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(0, 200, 500);

	// Camera node to allow custom camera keys
	cameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	cameraNode->setPosition(0, 200, 500);
	cameraNode->attachObject(mCamera);

	generateTerrain();

	entityMgr = new EntityMgr(mSceneMgr);
	generateEntities();
	entityMgr->selectNextEntity();
	// To avoid accidentally crashing program when attempting
	// to move an entity before selecting one first (at program start)
}

void As2::generateEntities(){
	Vector3 pos = Vector3(-500, 0, 0);
	for(int i = 0; i < 5; i++){
		entityMgr->CreateEntityOfTypeAtPosition("Cube", pos);
		pos.x += 250;
	}
	pos.x = -500;
	pos.z = -250;
	for(int i = 0; i < 5; i++){
		entityMgr->CreateEntityOfTypeAtPosition("Sphere", pos);
		pos.x += 250;
	}
}

void As2::cameraControl(const FrameEvent& fe){
	int move = 500;
	float rotate = 0.1;

	// Calculate direction for camera to move/turn
	Vector3 dirVec = Vector3::ZERO;
	if (mKeyboard->isKeyDown(OIS::KC_W))
		dirVec.z -= move;
	if (mKeyboard->isKeyDown(OIS::KC_S))
		dirVec.z += move;
	if (mKeyboard->isKeyDown(OIS::KC_E))
		dirVec.y += move;
	if (mKeyboard->isKeyDown(OIS::KC_F))
		dirVec.y -= move;
	if (mKeyboard->isKeyDown(OIS::KC_A)){
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			cameraNode->yaw(Degree(5 * rotate));
		else
			dirVec.x -= move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_D)){
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			cameraNode->yaw(Degree(-5 * rotate));
		else
			dirVec.x += move;
	}
	// Actual reposition/yaw
	cameraNode->translate(dirVec * fe.timeSinceLastFrame, Node::TS_LOCAL);
}

bool As2::frameRenderingQueued(const FrameEvent& fe){
	// Quit when Q key is pressed
	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_Q))
		return false;
	// Required for FPS and stuff to work
	mTrayMgr->frameRenderingQueued(fe);
	// Update camera movements
	cameraControl(fe);
	// Tick everything
	entityMgr->Tick(fe.timeSinceLastFrame);

	return true;
}

bool As2::keyReleased(const OIS::KeyEvent& ke){
	// This function controls the velocity through buffered input
	// I'm not sure how exactly it works but copying Tutorial 5
	// is the only way I got it to work
	switch(ke.key){
	case OIS::KC_NUMPAD8:
		entityMgr->selectedEntity->velocity.z -= speedChange;
		break;
	case OIS::KC_NUMPAD4:
		entityMgr->selectedEntity->velocity.x -= speedChange;
		break;
	case OIS::KC_NUMPAD2:
		entityMgr->selectedEntity->velocity.z += speedChange;
		break;
	case OIS::KC_NUMPAD6:
		entityMgr->selectedEntity->velocity.x += speedChange;
		break;
	case OIS::KC_NUMPAD9:
		entityMgr->selectedEntity->velocity.y += speedChange;
		break;
	case OIS::KC_NUMPAD3:
		entityMgr->selectedEntity->velocity.y -= speedChange;
		break;
	case OIS::KC_SPACE:
		entityMgr->selectedEntity->velocity = Vector3::ZERO;
		break;
	case OIS::KC_TAB:
		entityMgr->selectNextEntity();
		break;
	default:
		break;
	}
	return true;
}

void As2::generateTerrain(){
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
	As2 app;

	try {
	    app.go();
	} catch(Exception& e)  {
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
