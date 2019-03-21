/*
 * Aspect.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#include <Aspect.h>
#include <Entity381.h>

Aspect::Aspect(Entity381 *newEnt){
	entity = newEnt;
}

Aspect::~Aspect(){
}

void Aspect::Tick(float dt){
}

Physics::Physics(Entity381* newEnt):Aspect(newEnt){
}

Physics::~Physics(){
}

void Physics::Tick(float dt){
	// Update position (just math, not rendering)
	entity->position = entity->position + entity->velocity * dt;
}

Renderable::Renderable(Entity381* newEnt):Aspect(newEnt){
}

Renderable::~Renderable(){
}

void Renderable::Tick(float dt){
	// Make the entity appear in its new position
	entity->sceneNode->setPosition(entity->position);

	// Make the bounding box appear
	if(entity->isSelected){
		entity->sceneNode->showBoundingBox(true);
	}
	else{
		entity->sceneNode->showBoundingBox(false);
	}
}

Rotator::Rotator(Entity381* newEnt):Aspect(newEnt){
}

Rotator::~Rotator(){
}

void Rotator::Tick(float dt){
	// Rotate the entity
	entity->sceneNode->yaw(Ogre::Degree(0.05));
}
