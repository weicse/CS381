/*
 * InputMgr.cpp
 *
 *  Created on: Mar 7, 2019
 *      Author: wtong
 */

#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
using namespace Ogre;

InputMgr::InputMgr(Engine *engine) : Mgr(engine) {
	mInputMgr = NULL;
	mKeyboard = NULL;
	mMouse = NULL;
	// keyboardTimer = keyTime;
	deltaDesiredSpeed = 10.0f;
	deltaDesiredHeading = 10.0f;
}

InputMgr::~InputMgr() {
}

void InputMgr::Init(){

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

	  #if defined OIS_WIN32_PLATFORM
	  	  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	  	  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	  	  pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	  	  pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
	  #elif defined OIS_LINUX_PLATFORM
	  	  pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	  	  pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	  	  pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	  	  pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
	  #endif
	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(mInputMgr->createInputObject(OIS::OISKeyboard, true));
	  mMouse = static_cast<OIS::Mouse*>(mInputMgr->createInputObject(OIS::OISMouse, false));

	  int left, top;
	  unsigned int width, height, depth;

	  engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	  const OIS::MouseState &ms = mMouse->getMouseState();
	  ms.width = width;
	  ms.height = height;

	  mMouse->setEventCallback(this);
	  mKeyboard->setEventCallback(this);
}

void InputMgr::Stop(){
	if(mInputMgr){
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);
		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = NULL;
   	}
}

void InputMgr::Tick(float dt){
	mMouse->capture();
	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		engine->keepRunning = false;
	}
	cameraControl(dt);
	// UpdateVelocityAndSelection(dt);
}

void InputMgr::cameraControl(float dt){
	int move = 500;
	float rotate = 0.1;

	// Calculate direction for camera to move/turn
	Vector3 dirVec = Vector3::ZERO;
	if (mKeyboard->isKeyDown(OIS::KC_W)){
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			engine->gameMgr->cameraNode->pitch(Degree(5 * rotate));
		else
			dirVec.z -= move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_S)){
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			engine->gameMgr->cameraNode->pitch(Degree(-5 * rotate));
		else
			dirVec.z += move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_PGUP)){
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			engine->gameMgr->cameraNode->roll(Degree(5 * rotate));
		else
			dirVec.y += move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_PGDOWN)){
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			engine->gameMgr->cameraNode->roll(Degree(-5 * rotate));
		else
			dirVec.y -= move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_A)){
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			engine->gameMgr->cameraNode->yaw(Degree(5 * rotate));
		else
			dirVec.x -= move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_D)){
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			engine->gameMgr->cameraNode->yaw(Degree(-5 * rotate));
		else
			dirVec.x += move;
	}
	// Actual reposition/yaw
	engine->gameMgr->cameraNode->translate(dirVec * dt, Node::TS_LOCAL);
}

void InputMgr::LoadLevel(){
	// Not sure what's supposed to be in here
}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
	// This function controls the velocity through buffered input
	switch(ke.key){
	case OIS::KC_NUMPAD8:
		engine->entityMgr->selectedEntity->desiredSpeed += deltaDesiredSpeed;
		break;
	case OIS::KC_NUMPAD2:
		engine->entityMgr->selectedEntity->desiredSpeed -= deltaDesiredSpeed;
		break;
	case OIS::KC_NUMPAD4:
		engine->entityMgr->selectedEntity->desiredHeading -= deltaDesiredHeading;
		break;
	case OIS::KC_NUMPAD6:
		engine->entityMgr->selectedEntity->desiredHeading += deltaDesiredHeading;
		break;
	case OIS::KC_SPACE:
		engine->entityMgr->selectedEntity->velocity = Vector3::ZERO;
		engine->entityMgr->selectedEntity->desiredSpeed = 0;
		engine->entityMgr->selectedEntity->speed = 0;
		engine->entityMgr->selectedEntity->desiredHeading = engine->entityMgr->selectedEntity->heading;
		break;
	case OIS::KC_TAB:
		engine->entityMgr->selectNextEntity();
		break;
	default:
		break;
	}
	// Fix angle being < 0 or > 360
	engine->entityMgr->selectedEntity->desiredHeading = engine->entityMgr->selectedEntity->desiredHeading > 0 ? engine->entityMgr->selectedEntity->desiredHeading < 360 ? engine->entityMgr->selectedEntity->desiredHeading : engine->entityMgr->selectedEntity->desiredHeading - 360 : engine->entityMgr->selectedEntity->desiredHeading + 360;

	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me){
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id){
	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id){
	return true;
}
