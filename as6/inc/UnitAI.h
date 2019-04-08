/*
 * UnitAI.h
 *
 *  Created on: Apr 7, 2019
 *      Author: wtong
 */

#ifndef INC_UNITAI_H_
#define INC_UNITAI_H_

#include <Aspect.h>
#include <deque>

class Command;

class UnitAI : Aspect{
public:
	UnitAI(Entity381 *ent);
	~UnitAI();

	void Tick(float dt);

	void SetCommand(Command* c);
	void AddCommand(Command* c);

private:
	// Wanted to use a queue but it doesn't have a clear function
	std::deque<Command*> commands;
};

#endif /* INC_UNITAI_H_ */
