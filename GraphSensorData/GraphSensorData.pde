import processing.serial.*;

/*	GraphSensorData.pde
	Author: William Woodruff
	Takes data from a serial port used by the arduino (runtime specific), displaying it on a graph.
	Licensed under the MIT license.
*/

Serial port;
float x = 0;

void setup()
{
	size(800, 600); 
	String portStr = Serial.list()[2]; //important: dependent upon runtime circumstances.
	port = new Serial(this, portStr, 14400);
	background(#000000);
}

void draw()
{
	//nothing required here
}

void serialEvent(Serial port)
{
	int input = port.read();
	float y = height - input;
	stroke(#FFFFFF);
	line(x, height, x, height - input);
	if (x >= width)
	{
    	x = 0;
    	background(#000000);
 	}
	else
	{
   		x++;
	} 
}
