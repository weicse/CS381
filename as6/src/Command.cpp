/*
 * Command.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: wtong
 */

#include <Command.h>
#include <cmath>

Command::Command(Entity381* ent){
	entity = ent;
	isDone = false;
}

Command::~Command(){
}

void Command::tick(float dt){
}

void Command::stop(){
}

MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 loc) : Command(ent){
	targetLocation = loc;
}

MoveTo::~MoveTo(){
}

void MoveTo::tick(float dt){
	Ogre::Vector3 diff = targetLocation - entity->position;
	entity->desiredHeading = atan2(diff.z, diff.x) * (180/M_PI);
	entity->desiredHeading = entity->desiredHeading > 0 ? entity->desiredHeading < 360 ? entity->desiredHeading : entity->desiredHeading - 360 : entity->desiredHeading + 360;

	//Calculate velocity
	entity->desiredSpeed = entity->maxSpeed;

	if(entity->position.distance(targetLocation) < 10){
		isDone = true;
	}
	else{
		isDone = false;
	}
}

void MoveTo::stop(){
	entity->desiredSpeed = 0;
}

Intercept::Intercept(Entity381* ent, Entity381* tgt) : Command(ent){
	target = tgt;
}

Intercept::~Intercept(){
}

void Intercept::tick(float dt){
	//Calculate heading
	Ogre::Vector3 rel = target->velocity - entity->velocity;
	float dist = entity->position.distance(target->position);
	float t = dist / rel.length();
	Ogre::Vector3 diff = (target->position + target->velocity * t) - entity->position;
	entity->desiredHeading = atan2(diff.z, diff.x) * (180/M_PI);
	entity->desiredHeading = entity->desiredHeading > 0 ? entity->desiredHeading < 360 ? entity->desiredHeading : entity->desiredHeading - 360 : entity->desiredHeading + 360;

	//Calculate velocity
	entity->desiredSpeed = entity->maxSpeed;

	if(dist < 10)
		isDone = true;
	else
		isDone = false;
}

void Intercept::stop(){
	entity->desiredSpeed = 0;
}
