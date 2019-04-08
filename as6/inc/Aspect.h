/*
 * Aspect.h
 *
 *  Created on: Feb 24, 2019
 *      Author: wtong
 */

#ifndef ASPECT_H_
#define ASPECT_H_

#include <OgreVector3.h>

class Entity381; //Forward Declaration

class Aspect{
public:
  Aspect(Entity381*);
  virtual ~Aspect();
  Entity381* entity;
  virtual void Tick(float);
};

class Physics : Aspect{
public:
	Physics(Entity381*);
	~Physics();
	void Tick(float);
};


class Renderable : Aspect{
public:
	Renderable(Entity381*);
	~Renderable();
	void Tick(float);
};


class Rotator : Aspect{
public:
	Rotator(Entity381*);
	~Rotator();
	void Tick(float);
};

#endif /* ASPECT_H_ */
