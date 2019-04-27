#include "data.h"
#define CHAN 8
#define SPICHAN 0
#define SPEED 1000000

static int myfd;

int r_value(unsigned char buffer[3])
{
	int A = (buffer[1] << 8);
	int B = buffer[2];
	return (A + B);
}

struct spi_read spi_dec(int value[2])
{
	struct spi_read spi;
	spi.x = value[0];
	spi.y = value[1];
	spi.sw = value[2];
	return spi;
}

void* readAnalog()
{
	//setup SPI
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
			wiringPiSPIDataRW(SPICHAN, buffer, 3);
			//value[channel] = r_value(buffer);
			value[channel] = (buffer[1] << 8 + buffer[2]);
		}
		spi = spi_dec(value);
		sleep(SLEEP);
		//printf("<<==============================>>\n");
		printf("SW :%d", spi.x);
		printf("\tX :%d", spi.y);
		printf("\tY :%d\n", spi.sw);

	}
	close(myfd);
}
