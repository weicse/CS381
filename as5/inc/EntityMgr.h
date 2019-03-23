/*
 * EntityMgr.h
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include <Entity381.h>
#include <vector>
#include <Mgr.h>

class EntityMgr : public Mgr{
public:
  EntityMgr(Engine *);
  ~EntityMgr();

  std::vector<Entity381*> entities;
  Entity381* selectedEntity;
  int selectedEntityIndex;

  void CreateEntityOfTypeAtPosition(std::string, Ogre::Vector3);
  void selectNextEntity();
  void mouseNewSelect(int);

  void Tick(float dt);

private:
  void createEntity(std::string, Ogre::Vector3);
  void createDestroyer(Ogre::Vector3);
  void createCarrier(Ogre::Vector3);
  void createSpeedboat(Ogre::Vector3);
  void createFrigate(Ogre::Vector3);
  void createAlien(Ogre::Vector3);
  void createBanshee(Ogre::Vector3);
  int numEnts;
};

#endif /* INC_ENTITYMGR_H_ */
