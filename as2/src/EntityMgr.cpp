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

void EntityMgr::CreateEntity(std::string meshfilename, Ogre::Vector3 pos){
	Entity381 *newEnt = new Entity381(sceneMgr, meshfilename, pos, numEnts, "");
	numEnts++;
	entities.push_back(newEnt);
}

void EntityMgr::CreateCube(Ogre::Vector3 pos){
	Cube *newEnt = new Cube(sceneMgr, "cube.mesh", pos, numEnts, "Examples/Rockwall");
	numEnts++;
	entities.push_back((Entity381 *)newEnt);
}

void EntityMgr::CreateSphere(Ogre::Vector3 pos){
	Sphere *newEnt = new Sphere(sceneMgr, "sphere.mesh", pos, numEnts, "");
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
	if(entType == "Cube"){
		CreateCube(pos);
	}
	else if(entType == "Sphere"){
		CreateSphere(pos);
	}
	else{
		// If they accidentally forgot to specify
		CreateEntity("robot.mesh", pos);
	}
}

void EntityMgr::Tick(float dt){
	for(int i = 0; i < numEnts; i++){
		entities[i]->Tick(dt);
	}
}
