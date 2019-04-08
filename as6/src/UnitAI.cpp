/*
 * UnitAI.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: wtong
 */

#include <UnitAI.h>
#include <Entity381.h>
#include <Command.h>

UnitAI::UnitAI(Entity381* ent) : Aspect(ent){
}

UnitAI::~UnitAI(){
}

void UnitAI::Tick(float dt){
	if(!commands.empty()){
		// Run oldest command
		Command* runCommand = commands.front();
		runCommand->tick(dt);

		// Delete command after done
		if(runCommand->checkDone()){
			runCommand->stop();
			commands.pop_front();
			delete runCommand;
		}
	}
}

void UnitAI::AddCommand(Command *c){
	commands.push_back(c);
}

void UnitAI::SetCommand(Command* c){
	commands.clear();
	AddCommand(c);
}
