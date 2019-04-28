#include <wiringPiSPI.h>
#include <stdio.h>
#include <wiringPi.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "data.h"

int main()
{
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, readAnalog, NULL);
	sleep(.2);
	pthread_create(&thread_id, NULL, read_spi_input, NULL);
	pthread_join(thread_id, NULL);
	exit(0);
}