import processing.serial.*;

/*	MuscleGame.pde
	Author: William Woodruff
	Takes data from a serial port used by the arduino (runtme dependent),
	allowing the user to influence the motion of a falling ball.
	Licensed under the MIT license.
*/

Serial port;
Circle circle = new Circle(250, 50, 50);

int goodCount = 0;
int badCount = 0;

void setup()
{
	size(500, 800);
	smooth();
	line(100, 0, 100, 800);
	line(400, 0, 400, 800);
	stroke(255, 0, 0);
	line(100, 700, 400, 700);

	String portStr = Serial.list()[2];
	port = new Serial(this, portStr, 14400);
}

void draw()
{
	background(255);
	stroke(0, 0, 0);
	line(100, 0, 100, 800);
	line(400, 0, 400, 800);
	stroke(255, 0, 0);
	line(100, 700, 400, 700);
	circle.update();
	circle.checkCollisionWithLine();
	circle.draw();
}

void serialEvent(Serial port)
{
	int value = port.read();
	println(value);

	if (value < 120)
	{
		circle.ySpeed = -circle.ySpeed;
	}
}

class Circle
{
	float x, y, ySpeed, size;

	Circle(float x, float y, float size)
	{
		this.x = x;
		this.y = y;
		this.size = size;

		ySpeed = 2;
	}

	void update()
	{
		y += ySpeed;
	}

	void checkCollisionWithLine()
	{
		float r = size / 2;

		if (y > (height - r - 100))
			ySpeed = 0;
	}

	void draw()
	{
		fill(255);
		ellipse(x, y, size, size);
	}
}
