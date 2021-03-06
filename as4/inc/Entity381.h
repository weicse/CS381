/*
 * Entity381.h
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#ifndef INC_ENTITY381_H_
#define INC_ENTITY381_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>
#include <Engine.h>

class Entity381{
public:
	Entity381(Engine*, std::string, Ogre::Vector3, int, std::string);
	virtual ~Entity381();

	Engine* engine;

	int entityID;
	std::string entityName;

	Ogre::Vector3 position;
	Ogre::Vector3 velocity;
	float minSpeed, maxSpeed, speed;
	float heading, desiredSpeed, desiredHeading;
	float acceleration, turningRate;

	std::string meshfilename;
	Ogre::SceneNode* sceneNode;
	Ogre::Entity* ogreEntity;

	std::vector<Aspect*> aspects;
	bool isSelected;
	void Tick(float dt);
};

class Destroyer:Entity381{
public:
	Destroyer(Engine*, std::string, Ogre::Vector3, int, std::string);
	~Destroyer();
};

class Carrier:Entity381{
public:
	Carrier(Engine*, std::string, Ogre::Vector3, int, std::string);
	~Carrier();
};

class Speedboat:Entity381{
public:
	Speedboat(Engine*, std::string, Ogre::Vector3, int, std::string);
	~Speedboat();
};

class Frigate:Entity381{
public:
	Frigate(Engine*, std::string, Ogre::Vector3, int, std::string);
	~Frigate();
};

class Alien:Entity381{
public:
	Alien(Engine*, std::string, Ogre::Vector3, int, std::string);
	~Alien();
};

#endif /* INC_ENTITY381_H_ */
