#include "include.h"

int main()
{
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, readAnalog, NULL);
	pthread_join(thread_id, NULL);
	exit(0);
}
