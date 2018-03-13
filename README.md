# Event System / Event Bus / Messages channel for embedded systems #

There is a library that helps you to orginize your code for embedded systems. The events are one producer - one consumer thread safe. In the wild it means that you can create some channel between interapts and main cicle of program.

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
