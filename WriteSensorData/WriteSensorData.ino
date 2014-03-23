/*	WriteSensorData.ino
	Author: William Woodruff
	Interfaces with the Olimex EMG/EKG shield, feeding obtained data
	into the Arduino's serial terminal.
	Based on the example code provided by Olimex.
	Licensed under the MIT license.
*/

#include <compat/deprecated.h>
#include <FlexiTimer2.h>

#define NUMCHANNELS 6
#define HEADERLEN 4
#define PACKETLEN (NUMCHANNELS * 2 + HEADERLEN + 1)
#define SAMPFREQ 256                      
#define TIMER2VAL (1024/(SAMPFREQ))                          
#define CAL_SIG 	uint8_t sync	uint8_t sync	uint8_t versio	uint8_t coun	uint16_t data[6	uint8_t switche}

volatile unsigned char packet[PACKETLEN];
volatile unsigned char index;
volatile unsigned char current_channel;
volatile unsigned char counter = 0;
volatile unsigned char adc_value = 0;

void toggle_CAL_SIG(void)
{
	if (digitalRead(CAL_SIG) == HIGH)
	{
		digitalWrite(CAL_SIG, LOW);
	}
	else
	{
		digitalWrite(CAL_SIG, HIGH);
	}
}

void setup(void)
{
	noInterrupts();

	pinMode(CAL_SIG, OUTPUT);

	packet[0] = 0xa5; 
	packet[1] = 0x5a; 
	packet[2] = 2;    
	packet[3] = 0;    
	packet[4] = 0x02; 
	packet[5] = 0x00; 
	packet[6] = 0x02; 
	packet[7] = 0x00; 
	packet[8] = 0x02; 
	packet[9] = 0x00; 
	packet[10] = 0x02;
	packet[11] = 0x00;
	packet[12] = 0x02;
	packet[13] = 0x00;
	packet[14] = 0x02;
	packet[15] = 0x00;
	packet[2 * NUMCHANNELS + HEADERLEN] =  0x01;

	FlexiTimer2::set(TIMER2VAL, Timer2_Overflow_ISR);
	FlexiTimer2::start();

	Serial.begin(57600);

	interrupts();
}

void Timer2_Overflow_ISR(void)
{
	for (current_channel = 0; current_channel < 6; current_channel++)
	{
		adc_value = analogRead(current_channel);
		packet[((2*current_channel) + HEADERLEN)] = ((unsigned char) ((adc_value & 0xFF00) >> 8));
		packet[((2*current_channel) + HEADERLEN + 1)] = ((unsigned char) (adc_value & 0x00FF));
	}

	for (index = 4; index < 16; index++)
	{
		Serial.write(packet[index] & 0x3E);
	}

	packet[3]++;
	counter++;

	if (counter == 12)
	{
		counter = 0;
		toggle_CAL_SIG();
	}
}

void loop()
{
	__asm__ __volatile__ ("sleep");
}
