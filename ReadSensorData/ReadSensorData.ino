#include <compat/deprecated.h>
#include <FlexiTimer2.h>

#define NUMCHANNELS 6
#define HEADERLEN 4
#define PACKETLEN (NUMCHANNELS * 2 + HEADERLEN + 1)
#define SAMPFREQ 256                      
#define TIMER2VAL (1024/(SAMPFREQ))                          
#define LED1  13
#define CAL_SIG 9

// struct packet
// {
// 	uint8_t sync0;
//  	uint8_t sync1;
//  	uint8_t version;
//  	uint8_t count;
//  	uint16_t data[6];
//  	uint8_t switches;
// }

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

	TXBuf[0] = 0xa5;    //Sync 0
	TXBuf[1] = 0x5a;    //Sync 1
	TXBuf[2] = 2;       //Protocol version
	TXBuf[3] = 0;       //Packet counter
	TXBuf[4] = 0x02;    //CH1 High Byte
	TXBuf[5] = 0x00;    //CH1 Low Byte
	TXBuf[6] = 0x02;    //CH2 High Byte
	TXBuf[7] = 0x00;    //CH2 Low Byte
	TXBuf[8] = 0x02;    //CH3 High Byte
	TXBuf[9] = 0x00;    //CH3 Low Byte
	TXBuf[10] = 0x02;   //CH4 High Byte
	TXBuf[11] = 0x00;   //CH4 Low Byte
	TXBuf[12] = 0x02;   //CH5 High Byte
	TXBuf[13] = 0x00;   //CH5 Low Byte
	TXBuf[14] = 0x02;   //CH6 High Byte
	TXBuf[15] = 0x00;   //CH6 Low Byte 
	TXBuf[2 * NUMCHANNELS + HEADERLEN] =  0x01;

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
		packet[((2*current_channel) + HEADERLEN + 1)] = ((unsigned char) (adc_value & 0xFF00);
	}

	for (index = 4; index < 16; index++)
	{
		Serial.write(packet[index]);
	}

	packet[3]++;
	counter++;

	if (counter == 12)
	{
		counter = 0;
		toggle_CAL_SIG();
	}
}