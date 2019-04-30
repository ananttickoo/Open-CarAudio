#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "data.h"
#include "config.h" //this will be removed and config.c will give the values dynamically

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CHAN 8
#define SPICHAN 0
#define SPEED 1000000
#define True 1

static int myfd;
//struct spi_read spi;

int r_value(unsigned char buffer[3])
{
	int A = (buffer[1] << 8);
	int B = buffer[2];
	return (A + B);
}

struct spi_read spi_dec(int value[2])
{
	struct spi_read spi;
	spi.x = value[2];
	spi.y = value[1];
	spi.sw = value[0];
	return spi;
}

void* readAnalog()
{
	//setup SPI
	wiringPiSetup();
	if ((myfd = wiringPiSPISetup(SPICHAN, SPEED)) < 0)
	{
		printf("unable to open spi\n");
		//return -1;
	}
	int channel, value[2];
	struct spi_read spi;
	while (True)
	{
		channel = 0;
		for (; channel < 3; channel++)
		{
			printf("channel == > %d\n", channel);
			unsigned char buffer[3] = { 1 };
			buffer[1] = (CHAN + channel) << 4;
			if (wiringPiSPIDataRW(SPICHAN, buffer, 3) == -1)
			{
				printf("SPI failure: %s\n", strerror(errno));
				//spiFail = TRUE;
				//break;
			}
			printf("channel == > %d\n", channel);
			value[channel] = (int)((buffer[1] << 8) + buffer[2]);
		}
		spi = spi_dec(value);
		sleep(SLEEP);
		printf("<<==============================>>\n");
		printf("SW :%d", spi.sw);
		printf("\tX :%d", spi.x);
		printf("\tY :%d\n", spi.y);
		G_spi = spi;
	}
	close(myfd);
}


/*This snippet is suppose to read the values from
 variables of SPI output . Then convert them into
 action that should be passed to mpd.

 SPI READ -> ACTION
*/

//activate mutex.

void* read_spi_input()
{
	while (True)
	{
		int x, y, sw;
		x = 524;
		y = 537;
		sw = 20;
		for (int i = 0; i < 10; i++)
		{
			x = (G_spi.x + x) / 2;
			y = (G_spi.y + y) / 2;
			sw = (G_spi.sw + sw) / 2;
			sleep(.3);
		}
		//printf("%d\t%d\t%d\n", G_spi.sw, G_spi.x, G_spi.y);
		//printf("%d\t%d\t%d\n", sw, x, y);

	}
}



int main()
{
	pthread_t thread_id;
	printf("starting thread to read from SPI \n");
	pthread_create(&thread_id, NULL, readAnalog, NULL);
	sleep(.2);
	printf("starting thread to read interpert joystick \n");
	pthread_create(&thread_id, NULL, read_spi_input, NULL);
	pthread_join(thread_id, NULL);
	exit(0);
}