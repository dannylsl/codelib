#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <termios.h>
#include <errno.h>
#include <string.h>

#define SERIALPORT "/dev/ttyUSB1" 

int main()
{
	int fd;
	int len;
	int n = 0;      
	char read_buf[100];
	char write_buf[100];
	struct termios opt; 

	fd = open(SERIALPORT, O_RDWR | O_NOCTTY);    //默认为阻塞读方式
//	fd = open(SERIALPORT, O_RDWR | O_NOCTTY | O_NDELAY);    //nonblock
	if(fd == -1)
	{
		perror("open SERIALPORT failed");
		exit(0);
	}

	tcgetattr(fd, &opt);      
	cfsetispeed(&opt, B115200);
	cfsetispeed(&opt, B115200);
	//cfsetospeed(&opt, B9600);

	if(tcsetattr(fd, TCSANOW, &opt) != 0 )
	{     
		perror("tcsetattr error");
		return -1;
	}

	opt.c_cflag &= ~CSIZE;  
	opt.c_cflag |= CS8;   
	opt.c_cflag &= ~CSTOPB; 
	opt.c_cflag &= ~PARENB; 
	opt.c_cflag &= ~INPCK;
	opt.c_cflag |= (CLOCAL | CREAD);

	opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	opt.c_oflag &= ~OPOST;
	opt.c_oflag &= ~(ONLCR | OCRNL);    //添加的

	opt.c_iflag &= ~(ICRNL | INLCR);
	opt.c_iflag &= ~(IXON | IXOFF | IXANY);    //添加的

	opt.c_cc[VTIME] = 0;
	opt.c_cc[VMIN] = 0;

	tcflush(fd, TCIOFLUSH);

	printf("configure complete\n");

	fcntl(fd,F_SETFL,0);

	if(tcsetattr(fd, TCSANOW, &opt) != 0)
	{
		perror("serial error");
		return -1;
	}
	printf("start send and receive data\n");


	memset(write_buf,0,100);
	strcpy(write_buf,"HELLOWORLD");
	len = strlen(write_buf);

	while(1)
	{    
		n = 0;
		memset(read_buf,0,100);

		n = read(fd, read_buf, 5);	
		if(n < 0){
			printf("The device is crashed!!\n");
			perror("The device is crashed!");
			exit(0);
		}else
			printf("Receive from Merrifield:%s\n",read_buf);
/*
		n = write(fd, write_buf, strlen(write_buf));	
		if(n != len){
			printf("The device is crashed!!\n");
			perror("The device is crashed!");
			exit(0);
		}
*/
		printf("The device is alive\n");
		sleep(2);
	}
}
