#include <stdio.h> 
#include <errno.h> 
#include <fcntl.h>

#define DEV_NODE "/dev/csli_chrdev"


int main(void)
{
	int fd;
	unsigned char buf;
	ssize_t ret;

	fd = open(DEV_NODE, O_RDWR);
	if(fd == -1) {
		perror("open");
	}

	buf = 0xBE;
	ret = write(fd, &buf, 1);
	if(ret <= 0) {
		perror("write");
	}

	buf = 0x0;
	read(fd, &buf, 1);
	printf("read buf = 0x%x\n", buf);

	if( close(fd) != 0) {
		perror("close");
	}
	
	return 0;
}

