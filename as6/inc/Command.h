/*
 * Command.h
 *
 *  Created on: Apr 7, 2019
 *      Author: wtong
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_
#include <Entity381.h>

class Command{
public:
	Command(Entity381*);
	virtual ~Command();

	virtual void tick(float);
	virtual void stop();
	bool checkDone(){return isDone;}

protected:
	bool isDone;
	Entity381* entity;
};

class MoveTo : public Command{
public:
	MoveTo(Entity381*, Ogre::Vector3);
	~MoveTo();

	void tick(float);
	void stop();

protected:
	Ogre::Vector3 targetLocation;
};

class Intercept : public Command{
public:
	Intercept(Entity381*, Entity381*);
	~Intercept();

	void tick(float);
	void stop();

protected:
	Entity381* target;
};

#endif /* INC_COMMAND_H_ */
