#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <sys/ioctl.h> 
#include <sys/mman.h> 
#include <errno.h>
//#include <libv4l2-videodev.h>
#include <linux/videodev2.h>
#include <jpeglib.h>

#define WIDTH 320 
#define HEIGHT 240
#define V4L_DEVICE "/dev/video0"

int write_jpeg(char *filename,unsigned char *buf,int quality,int width, int height, int gray) {

	struct jpeg_compress_struct cinfo; 
	struct jpeg_error_mgr jerr; 
	FILE *fp; 
	int i;

	unsigned char *line; 
	int line_length;

	if (NULL == (fp = fopen(filename,"w"))) {

		fprintf(stderr,"grab: can't open %s: %s\n",filename,strerror(errno)); 
		return -1; 
	}

	cinfo.err = jpeg_std_error(&jerr); 
	jpeg_create_compress(&cinfo); 
	jpeg_stdio_dest(&cinfo, fp); 
	cinfo.image_width = width; 
	cinfo.image_height = height;

	cinfo.input_components = gray ? 1: 3;

	cinfo.in_color_space = gray ? JCS_GRAYSCALE: JCS_RGB; 
	jpeg_set_defaults(&cinfo);

	jpeg_set_quality(&cinfo, quality, TRUE); 
	jpeg_start_compress(&cinfo, TRUE);

	line_length = gray ? width : width * 3;

	for (i = 0, line = buf; i < height; i++, line += line_length) 
		jpeg_write_scanlines(&cinfo, &line, 1);

	jpeg_finish_compress(&(cinfo)); 
	jpeg_destroy_compress(&(cinfo)); 
	fclose(fp);

	return 0; 
}

int main() {

	unsigned char* buf; 
	int i,j; 
	int fd;

	int re;

	struct video_capability vcap; 
	struct video_channel vc; 
	struct video_mbuf mbuf; 
	struct video_mmap mm;

	fd = open(V4L_DEVICE, O_RDWR); 
	if(fd<=0) {

		perror("open"); 
		exit(1); 
	}

	if(ioctl(fd, VIDIOCGCAP, &vcap)<0) {

		perror("VIDIOCGCAP"); 
		exit(1); 
	}

	fprintf(stderr,"Video Capture Device Name : %s\n",vcap.name);

	for(i=0;i<vcap.channels;i++) {

		vc.channel = i;

		if(ioctl(fd, VIDIOCGCHAN, &vc)<0) {

			perror("VIDIOCGCHAN"); 
			exit(1); 
		}

		fprintf(stderr,"Video Source (%d) Name : %s\n",i, vc.name); 
	}

	vc.channel =1;
	vc.norm=1;

	if(ioctl(fd, VIDIOCSCHAN, &vc) < 0) {

		perror("VIDIOCSCHAN"); 
		exit(1); 
	}

	if(ioctl(fd, VIDIOCGMBUF, &mbuf) < 0) {

		perror("VIDIOCGMBUF"); 
		exit(1); 
	}

	fprintf(stderr,"the frames number is %d\n",mbuf.frames);

	buf = (unsigned char*)mmap(0, mbuf.size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	if((int)buf < 0) {

		perror("mmap"); 
		exit(1); 
	}

	mm.frame = 0;

	mm.height = HEIGHT; 
	mm.width = WIDTH;

	mm.format = VIDEO_PALETTE_RGB24;

	if(ioctl(fd, VIDIOCMCAPTURE, &mm)<0)

	{

		perror("VIDIOCMCAPTURE"); 
		exit(1); 
	}

	if(ioctl(fd, VIDIOCSYNC, &mm.frame)<0) {

		perror("VIDIOCSYNC"); 
		exit(1); 
	}

	if(-1 == (write_jpeg("./pic001.jpeg",buf,75,WIDTH,HEIGHT,0))) {

		printf("write_jpeg error\n"); 
		exit(1); 
	}

	munmap(buf,mbuf.size); 
	close(fd); 
}
