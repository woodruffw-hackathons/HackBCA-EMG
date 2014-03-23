import ddf.minim.*;
import processing.serial.*;

/*	PlaySensorData.pde
	Author: William
	Takes data from a serial port used by the arduino (runtme dependent),
	running it through Minim and generating noise based upon muscle extertion.
	Licensed under the MIT license.
*/

Serial port;
Minim minim;
AudioOutput output;

void setup()
{
	size(100, 100);
	minim = new Minim(this);
 	output = minim.getLineOut();
 	String portStr = Serial.list()[2];
	port = new Serial(this, portStr, 14400);
}

void draw()
{
	//nothing required here
}

void serialEvent(Serial port)
{
	int init_input = 440;
	if (init_input != 440)
	{
		output.playNote(1, 0.125, 440 + init_input);
	}
	else
	{
		output.playNote(1, 0.125, 440);
		init_input = port.read();
	}
}
