#include "data.h"
#include "config.h" //this will be removed and config.c will give the values dynamically

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CHAN 8
#define SPICHAN 0
#define SPEED 1000000

static int myfd;
struct spi_read spi;

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
			
			unsigned char buffer[3] = { 1 };
			buffer[1] = (CHAN + channel) << 4;
			printf("starting the reaad \n");
			if (wiringPiSPIDataRW(SPICHAN, buffer, 3) == -1)
			{
				printf("SPI failure: %s\n", strerror(errno));
				//spiFail = TRUE;
				//break;
			}
			value[channel] = (int)((buffer[1] << 8) + buffer[2]);
			printf("read channel %d \n", channel);
		}
		printf("read channel -- > %d \n", channel);
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
