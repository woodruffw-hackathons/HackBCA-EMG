import processing.serial.*;
Serial port;
float x = 0;

void setup()
{
 size(400, 300); 
 println(Serial.list());
 
 String portStr = Serial.list()[2];
 port = new Serial(this, portStr, 14400);
 background(#FFFFFF);
}

void draw()
{
}

void serialEvent (Serial port)
{
 int input = port.read();
 float y = height - input;
 stroke(#FFFFFF);
 line(x, height, x, height - input);
 if (x >= width) {
    x = 0;
    // clear the screen by resetting the background:
    background(#081640);
  }
  else {
    // increment the horizontal position for the next reading:
    x++;
  } 
}
