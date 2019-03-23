/*
 * Entity381.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#include <Entity381.h>
#include <GfxMgr.h>

std::string myStrConverter(int thatID){
	// Convert int to string, couldn't figure
	// out how to use C++11
	char buffer[100];
	sprintf(buffer, "%i", thatID);
	return std::string(buffer);
}

Entity381::Entity381(Engine* newEngine, std::string whichMesh, Ogre::Vector3 pos, int whatID, std::string materialName){

	engine = newEngine;

	meshfilename = whichMesh;
	position = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	entityID = whatID;
	isSelected = false;

	// Easy naming convention to help when debugging
	entityName = whichMesh + "_" + myStrConverter(entityID);

	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(ogreEntity);
	ogreEntity->setMaterialName(materialName);

	Physics* physics = new Physics(this);
	aspects.push_back((Aspect*) physics);
	Renderable* renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	Rotator* rotator = new Rotator(this);
	aspects.push_back((Aspect*)rotator);

	minSpeed = 0, maxSpeed = 0, speed = 0;
	heading = 0, desiredSpeed = 0, desiredHeading = 0;
	acceleration = 0, turningRate = 0;

	altitude = 0, desiredAltitude = 0, climbRate = 0;
	minHeight = 0, maxHeight = 0;
}

Entity381::~Entity381(){
}

void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

Destroyer::Destroyer(Engine* newEngine, std::string whichMesh, Ogre::Vector3 pos, int whatID, std::string materialName):Entity381(newEngine, whichMesh, pos, whatID, materialName){
	minSpeed = 0; // Ships can't go backwards
	maxSpeed = 150; // Decently fast I guess
	acceleration = 15;
	turningRate = 10;
}

Destroyer::~Destroyer(){
}

Carrier::Carrier(Engine* newEngine, std::string whichMesh, Ogre::Vector3 pos, int whatID, std::string materialName):Entity381(newEngine, whichMesh, pos, whatID, materialName){
	minSpeed = 0;
	maxSpeed = 200; // Fastest of all the ships
	acceleration = 20; // Should be able to get up to speed pretty fast
	turningRate = 5; // Slowest at turning
}

Carrier::~Carrier(){
}

Speedboat::Speedboat(Engine* newEngine, std::string whichMesh, Ogre::Vector3 pos, int whatID, std::string materialName):Entity381(newEngine, whichMesh, pos, whatID, materialName){
	minSpeed = 0;
	maxSpeed = 125;
	acceleration = 15;
	turningRate = 15;
}

Speedboat::~Speedboat(){
}

Frigate::Frigate(Engine* newEngine, std::string whichMesh, Ogre::Vector3 pos, int whatID, std::string materialName):Entity381(newEngine, whichMesh, pos, whatID, materialName){
	minSpeed = 0;
	maxSpeed = 75;
	acceleration = 10;
	turningRate = 12;
}

Frigate::~Frigate(){
}

Alien::Alien(Engine* newEngine, std::string whichMesh, Ogre::Vector3 pos, int whatID, std::string materialName):Entity381(newEngine, whichMesh, pos, whatID, materialName){
	minSpeed = 0;
	maxSpeed = 50; // Very slow because weak engine
	acceleration = 10; // Very agile, should be able to reach max speed fast
	turningRate = 45; // Turning abilities that defy physics
}

Alien::~Alien(){
}

Banshee::Banshee(Engine* newEngine, std::string whichMesh, Ogre::Vector3 pos, int whatID, std::string materialName):Entity381(newEngine, whichMesh, pos, whatID, materialName){
	minSpeed = 0;
	maxSpeed = 50;
	acceleration = 10;
	turningRate = 25;
	climbRate = 10;
	minHeight = 0;
	maxHeight = 100;
}

Banshee::~Banshee(){
}
