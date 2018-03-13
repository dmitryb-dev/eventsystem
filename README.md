# Event System / Event Bus / Messages channel for embedded systems #

There is a library that helps you to orginize your code for embedded systems. The events are one producer - one consumer thread safe. In the wild it means that you can create some channel between interrupts and main cicle of program.

## Data channel ##

### Overview ###

Let say we have next code:

    double temperature;
	char has_new_measurement;
    void temp_measurement_interrupt() 
	{
	    temperature = ...
		has_new_measurement = 1;
	}
	void handle_temp_change() 
	{
		... // do something with tmperature
		has_new_measurement = 0;
	}
	void main() 
	{
		while(1)
		{
			if (has_new_measurements)
			{
				handle_temp_change();
				has_new_measurements = 0;
			}
		}
	}
	
Disadvantages of this approach are obvious:

- Thread unsafity: what will be when we try to read temperature in `handle_temp_change` while `temp_measurement_interrupt` is writing new value?
- Leak of values, when several values have come but not yet handled, previous values is lost.
- Boilerplate code.
- Global variables.
 
 So with messages channel it can be changed to next:
 	
	#include "events-engine.h"
 
 	void handle_temp_change(double *temperature) 
	{
		... // do something with tmperature
	}
	
	DataStream(TemperatureMeasured, double, 3)
	{
		bindHandler(handle_temp_change);
	}
	
	void temp_measurement_interrupt() 
	{
		publishData(TemperatureMeasured, double* temperature) *temperature = ...
	}
	void main() 
	{
		while(1) handleEvent(TemperatureMeasured);
	}
	
Lets look at example above. Firstly you should declare channel with next code:

    DataStream(TemperatureMeasured, double, 3)
	{
		bindHandler(handle_temp_change);
	}
	
It means that we have channerl named `TemperatureMeasured`, with message type `double` and size `3`. So channel can store 3 messages. When more than 3 messages is come without handling, the new one will be lost.
And when some message is come `handle_temp_change` will be executed.

	void temp_measurement_interrupt() 
	{
		publishData(TemperatureMeasured, double* temperature) *temperature = ...
	}
	
`publishData` enables us to put some data into channel. Some place in channel will be allocated and become available via `temperature` pointer. Also you can put your code between brackets:

	void temp_measurement_interrupt() 
	{
		publishData(TemperatureMeasured, double* temperature) 
		{
			*temperature = ...
		}
	}

If channel doesn't have enough space for new message, code inside of block won't executed.

At the end we run hanling mechanism with `handleEvent(TemperatureMeasured)`. It checks if some messages exists inside of channel and call `handle_temp_change` handler when message occurs. It process just one message, not all messages in channel.

### Data stream definition ###

#### Handler binding ####

You can handle data right in stream definition without writing separate function.

	DataStream(KeyboardInput, int, 7)
	{
		int* keyCodePointer = getStreamData();
		keyHandler(keyCodePointer);
		
		int keyCode = getStreamDataValue();
		keyHandler(&keyCode);
		
		bindHandler(keyHandler);
	}
	
#### Stream without data ####

If you need just to notify about some event without any data inside, you can declare it as event:
	
	Event(PowerButtonPressed, 3)
	{
		bindListener(toggleDisplaySate);
	}
	
#### Ordering ####

You can guruntee, that some events won't be available before other event has handled:

	OrderedEvent(EventA, 2, defaultGroup) {}
	OrderedDataStream(EventB, int, 3, defaultGroup) {}
	
You pass group as third argument. Let say we have two events, firstly we have received EventB and after that EventA. So `handlerEvent(EventA)` will do nothing until `handleEvent(EventB)` is called.
You can specify you own group with next definition: `Group keaboardGroup;`. So events withing defaultGroup will be ordered and events keaboardGroup will be ordered inside of groups and events that belongs to different groups is not ordered.

### Put data in channel ###

You can put data with next construction:

	publishData(DataCome, double* data) 
	{
		*data = ...
	}
	
All data inside of brackets is thead safe, so it's not recomended to do something with data pointer outside of block. If you have just one expression curly brackets can be omitted:

	publishData(DataCome, double* data) *data = ...
	
Pay attantion to that it works only for DataStream and OrderedDataStream. If you want to fire event, you have to use `publishEvent(EventName)` construction.

#### Missing free space situation handling ####

If channel doesn't have enough space for new message code within blocks won't be executed. If you want to handle this situation you can just write `else` section:

	publishData(DataArrived, int* value) { }
	else
	{
		logError(); // just for example
	}
	
## Event system ##

You don't have need for write main function with handleEvent(...) calls chain. Instead of this it's recomended to define EventSystem:

	#include "simple-system.h"
	EventSystem
	{
		registerEvent(EventA);
		registerEvent(EventB);
	}
	void main()
	{
		runEventSystem();
	}
	
### Event system priorities ###

You can make some events more importent than others. So, when system is handling EventA it proccess all messages that lay in channel during one Event System Step, not just one as in case of EventB:

	EventSystem
	{
		HighPriorityregisterEvent(EventA);
		registerEvent(EventB);
	}
	
If you need for extended priorities, you can use prioritized event system (the definition is strict, you can't omit any block or change order of blocks, but you can leave block empty, eg. `LowPriority {}`):

	#include "prioritized-system.h"

	EventSystem
	{
		HighestPriority
		{
			registerEvent(HighEvent);
		}
		MediumPriority
		{
			registerEvent(MediumEvent);
		}
		LowPriority
		{
			registerEvent(LowEvent);
		}
	}
	
In addition for previous we will have handling of all events with high priority betwwen checking any other channel.
*Caution.* You can't have both of event systems. So you should to be careful to not include both systems:

	#include "prioritized-system.h"
	#include "simple-system.h" // ignored
	
### Event system lifecycle ###

If you want to do something in special cases you can defclare and register system events:

	SystemStart
	{
		bindListener(init);
	}
	SystemTick
	{
		bindListener(checkIsDataArrived);
	}
	SystemStop
	{
		bindListener(onStop);
	}

	EventSystem
	{
		registerEvent(SystemStop);
		registerEvent(SystemStart);
		registerEvent(SystemTick);
	}
	
Also you can omit registratrion of events by `#define SYSTEM_LIFECYCLE`. But in this case you must define all events!

	#define SYSTEM_LIFECYCLE

	SystemStart {}
	SystemTick {}
	SystemStop{}

	EventSystem { /* All events will be registered automaticaly */ }
	
If you want to stop system, you can publish stop event: `publishEvent(SystemStop)`. After that, loop in runEventSystem will be broken.

## Components ##

### Lifecicle ###

It just a additional util to avoid using global variables.

	struct TemperatureSensor 
	{
		double id;
		double value;
		double precission;
	}
	Component(TemperatureSensor, DefaultTemparatureSensor) // DefaultTemparatureSensor - just a name
	{
		TemperatureSensor sensor = ...
		return sensor;
	}
	
After that you can call Get(DefaultTemparatureSensor) to acquire pointer to component. It creates singleton, instance will be created automatically. Bear in mind, that it add `if` condition to check is component was created or not 
every time, when you call Get(...). If you want to acquire value instead of pointer you can call `Value(ComponentName)` instead.
So next lines do the same things:

	*Get(Comp) = ...
	Set(Comp, ...)
	Value(Comp) = ...
	
If you want to reset component state and call init code, defined in `Component(...) { init code }`, you can call `Reset(Comp)`

To create new Comoponent instead of acquiring of existing global you can call `Create(Comp)`:

	Component(int, IntegerComp)
	{
		return 3;
	}
	void main()
	{
		int *a = Get(IntegerComp); // a = 3;
		int *b = &Create(IntegerComp); // b = 3
		Set(IntegerComp, 777); // a = 777, b = 3
	}
	
### Binding to events ###

You can use components inside of any event:

	Component(int, dataComp) { return 3; }
	Component(char, tickComp) { return 7; }

	void dataHandler(int *dataComp, double *arrivedData) { ... }
	void tickListener(char *tickComp) { ... } 

	DataStream(Data, double, 3)
	{
		bindHandlerComp(dataComp, dataHandler);
	}
	SystemTick
	{
		bindListenerComp(tickComp, tickListener);
	}