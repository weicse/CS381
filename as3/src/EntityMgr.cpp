/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#include <EntityMgr.h>

EntityMgr::EntityMgr(Ogre::SceneManager* newSceneMgr){
	selectedEntity = 0;
	sceneMgr = newSceneMgr;
	numEnts = 0;
	selectedEntityIndex = -1;
}

EntityMgr::~EntityMgr(){
}

void EntityMgr::createEntity(std::string meshfilename, Ogre::Vector3 pos){
	Entity381 *newEnt = new Entity381(sceneMgr, meshfilename, pos, numEnts, "");
	numEnts++;
	entities.push_back(newEnt);
}

void EntityMgr::createDestroyer(Ogre::Vector3 pos){
	Destroyer *newEnt = new Destroyer(sceneMgr, "ddg51.mesh", pos, numEnts, "Examples/Ninja");
	numEnts++;
	entities.push_back((Entity381 *)newEnt);
}

void EntityMgr::createCarrier(Ogre::Vector3 pos){
	Carrier *newEnt = new Carrier(sceneMgr, "cvn68.mesh", pos, numEnts, "Examples/TudorHouse");
	numEnts++;
	entities.push_back((Entity381 *)newEnt);
}

void EntityMgr::createSpeedboat(Ogre::Vector3 pos){
	Speedboat *newEnt = new Speedboat(sceneMgr, "cigarette.mesh", pos, numEnts, "Examples/Robot");
	numEnts++;
	entities.push_back((Entity381 *)newEnt);
}

void EntityMgr::createFrigate(Ogre::Vector3 pos){
	Frigate *newEnt = new Frigate(sceneMgr, "sleek.mesh", pos, numEnts, "Examples/Rockwall");
	numEnts++;
	entities.push_back((Entity381 *)newEnt);
}

void EntityMgr::createAlien(Ogre::Vector3 pos){
	Alien *newEnt = new Alien(sceneMgr, "alienship.mesh", pos, numEnts, "");
	numEnts++;
	entities.push_back((Entity381 *)newEnt);
}

void EntityMgr::selectNextEntity(){
	if(selectedEntityIndex >= numEnts - 1) {
		// Wrap around
		selectedEntityIndex = 0;
	}
	else {
		selectedEntityIndex++;
	}
	if(selectedEntity != 0){
		// Update so that other entities don't
		// count as selected
		selectedEntity->isSelected = false;
	}
	selectedEntity = entities[selectedEntityIndex];
	selectedEntity->isSelected = true;
}

void EntityMgr::CreateEntityOfTypeAtPosition(std::string entType, Ogre::Vector3 pos){
	if(entType == "Destroyer"){
		createDestroyer(pos);
	}
	else if(entType == "Carrier"){
		createCarrier(pos);
	}
	else if(entType == "Speedboat"){
		createSpeedboat(pos);
	}
	else if(entType == "Frigate"){
		createFrigate(pos);
	}
	else if(entType == "Alien"){
		createAlien(pos);
	}
	else{
		// If they accidentally forgot to specify
		createEntity("ninja.mesh", pos);
	}
}

void EntityMgr::Tick(float dt){
	for(int i = 0; i < numEnts; i++){
		entities[i]->Tick(dt);
	}
}
