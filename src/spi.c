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

void* readAnalog()
{
	//setup SPI
	if ((myfd = wiringPiSPISetup(SPICHAN, SPEED)) < 0)
	{
		printf("unable to open spi\n");
		//return -1;
	}
	int channel, value[2];
	while (True)
	{
		channel = 0;
		for (; channel < 3; channel++)
		{
			unsigned char buffer[3] = { 1 };
			buffer[1] = (CHAN + channel) << 4;
			wiringPiSPIDataRW(SPICHAN, buffer, 3);
			value[channel] = r_value(buffer);
		}
		sleep(.1);
		//printf("<<==============================>>\n");
		printf("SW :%d", value[0]);
		printf("\tX :%d", value[1]);
		printf("\tY :%d\n", value[2]);

	}
	close(myfd);
}
