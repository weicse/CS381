/*
 * Entity381.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#include <Entity381.h>

std::string myStrConverter(int thatID){
	// Convert int to string, couldn't figure
	// out how to use C++11
	char buffer[100];
	sprintf(buffer, "%i", thatID);
	return std::string(buffer);
}

Entity381::Entity381(Ogre::SceneManager* sceneMgr, std::string whichMesh, Ogre::Vector3 pos, int whatID, std::string materialName){

	meshfilename = whichMesh;
	position = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	entityID = whatID;
	isSelected = false;

	// Easy naming convention to help when debugging
	entityName = whichMesh + "_" + myStrConverter(entityID);

	ogreEntity = sceneMgr->createEntity(meshfilename);
	sceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(ogreEntity);
	ogreEntity->setMaterialName(materialName);

	Physics* physics = new Physics(this);
	aspects.push_back((Aspect*) physics);
	Renderable* renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	Rotator* rotator = new Rotator(this);
	aspects.push_back((Aspect*)rotator);

	speedChange = 0;
}

Entity381::~Entity381(){
}

void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

Cube::Cube(Ogre::SceneManager* sceneMgr, std::string whichMesh, Ogre::Vector3 pos, int whatID, std::string materialName):Entity381(sceneMgr, whichMesh, pos, whatID, materialName){
	// I assume this was what was desired. Originally, I had thought
	// to just call the Entity381 constructor but I wasn't sure if
	// that was acceptable (call during cube/sphere creation)
	speedChange = 75;
}

Cube::~Cube(){
}

Sphere::Sphere(Ogre::SceneManager* sceneMgr, std::string whichMesh, Ogre::Vector3 pos, int whatID, std::string materialName):Entity381(sceneMgr, whichMesh, pos, whatID, materialName){
	// They're smaller so they move slower right?
	speedChange = 25;
}

Sphere::~Sphere(){
}
