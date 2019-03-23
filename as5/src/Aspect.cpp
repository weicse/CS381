/*
 * Aspect.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#include <Aspect.h>
#include <Entity381.h>
// #include <cmath>

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
	// Update speed (limited by acceleration, not instant increase)
	// Accelerating
	if(entity->desiredSpeed > entity->speed){
		entity->speed += entity->acceleration * dt;
	}
	// Decelerating
	else if (entity->desiredSpeed < entity->speed){
		entity->speed -= entity->acceleration * dt;
	}
	// Fix if speed is out of bounds (> max or < min)
	entity->speed = entity->speed > entity->minSpeed ? entity->speed < entity->maxSpeed ? entity->speed : entity->maxSpeed : entity->minSpeed;

	// Turning clockwise
	if(entity->desiredHeading > entity->heading){
		if(entity->desiredHeading - entity->heading > 180){
			entity->heading -= entity->turningRate * dt;
		}
		else{
			entity->heading += entity->turningRate * dt;
		}
	}
	// Counter-clockwise
	else if (entity->desiredHeading < entity->heading){
		if(entity->desiredHeading - entity->heading < -180){
			entity->heading += entity->turningRate * dt;
		}
		else{
			entity->heading -= entity->turningRate * dt;;
		}
	}
	// Fix angle being < 0 or > 360
	entity->heading = entity->heading > 0 ? entity->heading < 360 ? entity->heading : entity->heading - 360 : entity->heading + 360;
	// Not sure why this doesn't work, should be an Ogre problem
	// entity->heading = abs(fmod(entity->heading, 360));

	// Calculate x and z coordinates from sin and cos
	entity->velocity.z = Ogre::Math::Sin(Ogre::Degree(entity->heading)) * entity->speed;
	entity->velocity.x = Ogre::Math::Cos(Ogre::Degree(entity->heading)) * entity->speed;

	// Calculate flying physics
	if(entity->desiredAltitude < entity->altitude){
		entity->altitude -= entity->climbRate * dt;
	}
	else if (entity->desiredAltitude > entity->altitude){
		entity->altitude += entity->climbRate * dt;
	}
	// Fix if height is out of bounds (> max or < min)
	entity->altitude = entity->altitude > entity->minHeight ? entity->altitude < entity->maxHeight ? entity->altitude : entity->maxHeight : entity->minHeight;
	entity->position.y = entity->altitude;

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
	entity->sceneNode->resetOrientation(); // Delete afterwards
	entity->sceneNode->yaw(Ogre::Degree(-entity->heading));
}
