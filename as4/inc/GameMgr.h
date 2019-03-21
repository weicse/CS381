/*
 * GameMgr.h
 *
 *  Created on: Mar 7, 2019
 *      Author: wtong
 */

#ifndef INC_GAMEMGR_H_
#define INC_GAMEMGR_H_

#include <Mgr.h>

class GameMgr : public Mgr{
public:
	GameMgr(Engine *);
	virtual ~GameMgr();

	void Init();
	void LoadLevel();

	int surfaceHeight;

	void generateTerrain();
	void generateEntities();

	Ogre::SceneNode *cameraNode;
};

#endif /* INC_GAMEMGR_H_ */
