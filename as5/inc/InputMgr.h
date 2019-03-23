/*
 * InputMgr.h
 *
 *  Created on: Mar 7, 2019
 *      Author: wtong
 */

#ifndef INPUTMGR_H_
#define INPUTMGR_H_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include <Mgr.h>

class Engine;

class InputMgr : public Mgr, public OIS::KeyListener, public OIS::MouseListener{

public:
	InputMgr(Engine *engine);
	virtual ~InputMgr();

	// All these needed for Engine.cpp to work
	virtual bool keyPressed(const OIS::KeyEvent&);
	virtual bool keyReleased(const OIS::KeyEvent&);
	virtual bool mouseMoved(const OIS::MouseEvent&);
	virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
	virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
	virtual void mouseSelect(const OIS::MouseEvent&);

	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;

	void Init();
	void Stop();
	void Tick(float dt);
	void LoadLevel();

	float deltaDesiredSpeed, deltaDesiredHeading, deltaDesiredAltitude;
	void cameraControl(float dt);
};

#endif /* INC_INPUTMGR_H_ */
