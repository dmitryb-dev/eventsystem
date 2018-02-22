// The same name as in simple-system.h to avoid using of both systems
#ifndef SYSTEM_ENGINE_H
#define SYSTEM_ENGINE_H

#include "system.h"

/*
 * Defines prioritized event system. The run function will look like:
 * while(1)
 * {
 * 		while (handleMediumPriority()); // until all events handled
 *
 * 		while (handleHighestPriority());
 * 		handleLowPriority1();
 * 		while (handleHighestPriority());
 * 		handleLowPriority2();
 * }
 *
 * The definition of system must be exactly next (order of priorities is strict):
 * EventSystem {
 * 		HighestPriority {
 * 			...
 * 		}
 * 		MediumPriority {
 * 			...
 * 		}
 * 		LowPriority {
 * 			...
 * 		}
 * }
 */
int _evs_handleHighestPriority();
int _evs_handleMediumPriority();
void _evs_handleLowPriority();


int isHighestLevel; // default value for medium and low level
char somethingWasHandled; // default value for low level

#define EventSystem void _evs_preStart()
#define HighestPriority \
	}\
	int _evs_handleHighestPriority() \
	{ \
		int isHighestLevel = 1; \
		char somethingWasHandled = 0;

#define MediumPriority \
		return somethingWasHandled; \
	} \
	int _evs_handleMediumPriority() \
	{ \
		char somethingWasHandled = 0;

#define LowPriority \
		return somethingWasHandled; \
	} \
	void _evs_handleLowPriority() \
	{


#define registerEvent(EventName) \
	somethingWasHandled += _evs_handle##EventName(); \
	if (!isHighestLevel) while(_evs_handleHighestPriority())


void systemStep()
{
	while (_evs_handleMediumPriority());
	_evs_handleLowPriority();
}


#endif
