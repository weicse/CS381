/*
 * Entity381.h
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#ifndef INC_ENTITY381_H_
#define INC_ENTITY381_H_

#include <Aspect.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>

class Entity381{
public:
  Entity381(Ogre::SceneManager*, std::string, Ogre::Vector3, int, std::string);
  virtual ~Entity381();

  int entityID;
  std::string entityName;

  Ogre::Vector3 position;
  Ogre::Vector3 velocity;
  float speedChange;

  std::string meshfilename;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity* ogreEntity;

  std::vector<Aspect*> aspects;
  bool isSelected;
  void Tick(float dt);
};

class Cube:Entity381{
public:
	Cube(Ogre::SceneManager*, std::string, Ogre::Vector3, int, std::string);
	~Cube();
};

class Sphere:Entity381{
public:
	Sphere(Ogre::SceneManager*, std::string, Ogre::Vector3, int, std::string);
	~Sphere();
};

#endif /* INC_ENTITY381_H_ */
