// FOR MORE DESCRIPTION		http://www.cnblogs.com/emouse/archive/2013/03/04/2943243.html
#ifndef _V4L2_H_
#define _V4L2_H_

#include <stdio.h>
#include <stdlib.h> //stdio.h and stdlib.h are needed by perror function
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> //O_RDWR
#include <unistd.h>
#include <sys/mman.h> //unistd.h and sys/mman.h are needed by mmap function
#include <stdbool.h>//false and true
#include <sys/ioctl.h>
#include <linux/videodev2.h>//v4l2 API
#include <string.h> //memset
#include <errno.h>	//errno

struct buffer{
	void *	start;
	size_t	length;
};
typedef struct _v4l2_struct
{
	int fd;
	int n_buffers;
	struct v4l2_capability capability;
	struct v4l2_format fmt;
	struct buffer* buffers;
	struct v4l2_buffer buf;
}v4l2_device;

extern int v4l2_open(char*,v4l2_device*);
extern int v4l2_close(v4l2_device*);
extern int v4l2_get_capability(v4l2_device*);


#define DEFAULT_DEVICE "/dev/video0"
int v4l2_open(char *dev,v4l2_device *vd)
{
	if(!dev)
		dev=DEFAULT_DEVICE;
	if((vd->fd=open(dev,O_RDWR))<0)
	{
		perror("v4l2_open fail");
		return -1;
	}
	if(v4l2_get_capability(vd))
		return -1;
	printf("video capture device name:%s\n",vd->capability.driver);
	return 0;
}

int v4l2_close(v4l2_device *vd)
{
	close(vd->fd);
	return 0;
}

int v4l2_get_capability(v4l2_device *vd)
{
	if(ioctl(vd->fd,VIDIOC_QUERYCAP,&vd->capability)<0)
	{ 
		perror("v4l2_get_capability fail");
		return -1;
	}
	// printf("V4L2_CAP_VIDEO_CAPTURE:%x\n",V4L2_CAP_VIDEO_CAPTURE);
	// printf("V4L2_CAPABILITIES:%x\n",vd->capability.capabilities);
	if(vd->capability.capabilities & V4L2_CAP_VIDEO_CAPTURE){
		printf("V4L2_CAP_VIDEO_CAPTURE: This device support Image Retrieve!\n");
	}
	return 0; 
}
//Show Format Supported
void v4l2_show_support_fmt(v4l2_device*vd){
	struct v4l2_fmtdesc fmt;
	fmt.index = 0;
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	printf("Support format:\n");
	for(fmt.index=0;fmt.index<100;fmt.index++){
		if(	ioctl(vd->fd,VIDIOC_ENUM_FMT,&fmt)==0){

			printf("\t%d.%s\n",fmt.index+1,fmt.description);
		}	
	}
	/*while(ioctl(vd->fd,VIDIOC_ENUM_FMT,&fmt)==0){
	//printf("\t%d.%s\n",fmtdesc.index+1,fmtdesc.description);
	//fmtdesc.index++;
	printf("{ pixelformat = '%c%c%c%c', description = '%s' }\n",
	fmt.pixelformat & 0xFF, (fmt.pixelformat >> 8) & 0xFF,
	(fmt.pixelformat >> 16) & 0xFF, (fmt.pixelformat >> 24) & 0xFF,
	fmt.description);
	fmt.index++;
	}*/
}

int v4l2_set_capture_fmt(v4l2_device*vd){
	int file_length;
	memset(&(vd->fmt),0,sizeof(vd->fmt));		
	vd->fmt.type				= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vd->fmt.fmt.pix.height		= 240;
	vd->fmt.fmt.pix.width		= 320;
	vd->fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	vd->fmt.fmt.pix.field		= V4L2_FIELD_INTERLACED;	
	if(ioctl(vd->fd,VIDIOC_S_FMT, &vd->fmt)<0){
		perror("VIDIOC_S_FMT ERROR");
		return -1;
	}
	file_length = vd->fmt.fmt.pix.bytesperline * vd->fmt.fmt.pix.height;
	return file_length;
}

// Return the count of Buffers requested
int v4l2_apply_capture_buffer(v4l2_device*vd){
	struct v4l2_requestbuffers req;
	memset(&req,0,sizeof(req));		

	req.count	= 4;
	req.type	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory  = V4L2_MEMORY_MMAP;

	if(ioctl(vd->fd, VIDIOC_REQBUFS, &req)){
		perror("VIDIOC_REQBUFS ERROR");	
		return -1;
	}

	if(req.count < 2){
		printf("Insufficient buffer memory\n");
		return -1;
	}
	vd->n_buffers = req.count;
	return req.count;
}

int v4l2_set_capture_buffer(v4l2_device*vd){
	unsigned char n_buffers;
	struct v4l2_buffer buf;
	unsigned int i;
	enum v4l2_buf_type type;

	vd->buffers =calloc(vd->n_buffers,sizeof(*(vd->buffers)));

	if(!vd->buffers){
		perror("CALLOC BUFFERS ERROR");
		exit(EXIT_FAILURE);
	}

	for(n_buffers = 0; n_buffers < vd->n_buffers; n_buffers++){
		memset(&buf,0,sizeof(buf));	
		buf.type	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory  = V4L2_MEMORY_MMAP;
		buf.index	= n_buffers;

		if(-1 == ioctl(vd->fd, VIDIOC_QUERYBUF, &buf)){
			perror("VIDIOC_QUERYBUF ERROR");
			exit(EXIT_FAILURE);
		}

		vd->buffers[n_buffers].length	= buf.length;
		vd->buffers[n_buffers].start	= mmap(NULL,
											buf.length,
											PROT_READ | PROT_WRITE, 
											MAP_SHARED,
											vd->fd,buf.m.offset);
		if(MAP_FAILED == vd->buffers[n_buffers].start){
			perror("MMAP FAILED!\n");
			exit(EXIT_FAILURE);
		}
	}

	//PUT BUFFERS INTO QUEUE
	for(i = 0; i < n_buffers; i++){
		memset(&buf,0,sizeof(buf));	
		buf.type	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory  = V4L2_MEMORY_MMAP;
		buf.index	= i;

		if(-1 == ioctl(vd->fd, VIDIOC_QBUF, &buf)){  //
			perror("VIDIOC_QBUF ERROR");	
			exit(EXIT_FAILURE);
		}
	}
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if(-1 ==ioctl(vd->fd,VIDIOC_STREAMON, &type)){
		perror("VIDIOC_STREAMON ERROR");	
		exit(EXIT_FAILURE);
	}
}

int v4l2_read_frame(v4l2_device*vd){
	unsigned int i;
	memset(&(vd->buf),0,sizeof(vd->buf));

	vd->buf.type	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vd->buf.memory  = V4L2_MEMORY_MMAP;

	if(-1==(ioctl(vd->fd, VIDIOC_DQBUF, &vd->buf))){
		perror("READ FREAME VIDIOC_DQBUF ERROR");
		exit(EXIT_FAILURE);
	} // GET A FRAME FROM BUFFER
				
	ioctl(vd->fd,VIDIOC_QBUF, &vd->buf);
	return 0;
}

// Check camera available and get a picture
int v4l2_get_frame_yuyv(v4l2_device*vd){
	fd_set fds;
	struct timeval tv;
	int r;

	while(1){
		FD_ZERO(&fds);
		FD_SET(vd->fd,&fds);

		tv.tv_sec	= 2;
		tv.tv_usec	= 0;

		r = select(vd->fd+1, &fds, NULL, NULL, &tv);

		if(-1 == r){
			perror("SELECT ERROR");
			exit(EXIT_FAILURE);
		}
		if(0 == r){
			fprintf(stderr, "SELECT TIMEOUT");
			exit(EXIT_FAILURE);
		}
			
		if(v4l2_read_frame(vd)==0)
			break;
	}
}

int v4l2_release_capture_buffer(v4l2_device*vd){
	unsigned int i;
	for(i =0; i < vd->n_buffers;++i){
		if(-1==munmap(vd->buffers[i].start, vd->buffers[i].length)){	
			perror("MUNMAP ERROR");
			exit(EXIT_FAILURE);
		}
	}
}

#endif
