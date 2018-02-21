// The same name as in simple-system.h to avoid using of both systems
#ifndef SYSTEM_ENGINE_H
#define SYSTEM_ENGINE_H

#include "system.h"

/*
 * Define prioritized event system. The run function will look like:
 * while(1)
 * {
 * 		while (handleMediumPriority()); // until all events handled
 *
 * 		while (handleHighestPriority());
 * 		handleLowPriority1();
 * 		while (handleHighestPriority());
 * 		handleLowPriority2();
 * }
 */

int handleHighestPriority();
int handleMediumPriority();
void handleLowPriority();

int isHighestLevel; // default value for medium and low level
char somethingWasHandled; // default value for low level
#define HighestLevel \
	int handleHighestPriority() \
	{ \
		int isHighestLevel = 1; \
		char somethingWasHandled = 0;

#define MediumLevel \
		return somethingWasHandled; \
	} \
	int handleMediumPriority() \
	{ \
		char somethingWasHandled = 0;

#define LowLevel \
		return somethingWasHandled; \
	} \
	void handleLowPriority() \


#define registerEvent(EventName) \
	somethingWasHandled += handle##EventName(); \
	if (!isHighestLevel) while(handleHighestPriority())


void systemStep()
{
	while (handleMediumPriority());
	handleLowPriority();
}


#endif
