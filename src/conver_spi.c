#include "data.h"
#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include <unistd.h>
#define True 1
/*This snippet is suppose to read the values from 
 variables of SPI output . Then convert them into
 action that should be passed to mpd.

 SPI READ -> ACTION 
*/

//activate mutex.

void* read_spi_input()
{
	while(True)
	{
		int x, y, sw;
		x = 524;
		y = 537;
		sw = 20;
		for(int i = 0; i < 10; i++)
		{
			x = (G_spi.x + x) / 2;
			y = (G_spi.y + y) / 2;
			sw = (G_spi.sw + sw) / 2;
			sleep(.3);
		}
		printf("%d\t%d\t%d\n", G_spi.sw, G_spi.x, G_spi.y);
		//printf("%d\t%d\t%d\n", sw, x, y);

	}
}