#include <stdio.h>
#include <fcntl.h>
#define DEVICE_NAME "/dev/leds"
int main(int argc, char** argv)
{
	int fd = -1;
	int val = 0;
	fd = open(DEVICE_NAME, O_RDWR);
	if (fd == -1)
	{
		printf("Failed to open device %s./n", DEVICE_NAME);
		return -1;
	}

	ioctl(fd, 1, 2); // open led 3 
	close(fd);
	return 0;
}
