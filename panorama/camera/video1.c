#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <libv4l1-videodev.h>

#define HEIGHT	240
#define WIDTH	320
#define PIXELS  2

int main(){

	int fd;
	struct video_capability vcap; 
	struct video_picture pic;
	struct video_mbuf mbuf; 
	unsigned char *buf; 
	struct video_mmap mm;
	FILE *fp;
	

	fd = open("/dev/video0",O_RDWR);
	if(fd < 0){
		perror("fd open failed");
		exit(0);
	}
	printf("waitting...\n");
	sleep(1);

	if(ioctl(fd, VIDIOCGCAP, &vcap)<0){
		perror("VIDIOCGCAP ERROR");
		exit(0);
	}
	printf("maxheight=%d\n",vcap.maxheight);
	printf("Video Capture Device Name:%s\n",vcap.name);

	if(ioctl(fd, VIDIOCGPICT, &pic) < 0){
		perror("VIDIOCGPICT ERROR:");	
		exit(0);
	}

	if(ioctl(fd, VIDIOCSPICT, &pic) < 0){
		perror("VIDIOCSPICT ERROR");	
		exit(0);
	}
	if(ioctl(fd, VIDIOCGMBUF, &mbuf) < 0){
		perror("VIDIOCGMBUF ERROR");	
		exit(0);
	}

	mm.frame  = 0;
	mm.height = 240;
	mm.width  = 320;
	mm.format = VIDEO_PALETTE_RGB565;

	buf = (unsigned char*)mmap(0,mbuf.size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	ioctl(fd,VIDIOCMCAPTURE,&mm);
	ioctl(fd,VIDIOCSYNC,&mm.frame);

	remove("grab_pic_mmap");
	fp = fopen("grab_pic_mmap","w");
	fwrite(buf+mbuf.offsets[mm.frame],mm.height*mm.width*2,1,fp);
	fclose(fp);

	munmap(buf,mbuf.size);
	close(fd);

		
	
}
