#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "yuyv2rgb.h"

#define YUYVFILE	"yuyv.bmp"
#define RGBFILE		"rgb_pakage2.bmp"
#define HEADER_LEN 54

#define HEIGHT	240
#define WIDTH	320

int main(int argc,char*argv){
	FILE *fp_in,*fp_out;
	unsigned char*rgb;
	unsigned char bmpHeader[HEADER_LEN];
	unsigned char yuyv[HEIGHT*WIDTH*2];

	if(NULL == (fp_in=fopen(YUYVFILE,"r+"))){
		perror("YUYVFILE OPEN ERROR");	
		return -1;
	};

	if(NULL == (fp_out=fopen(RGBFILE,"w+"))){
		perror("YUYVFILE OPEN ERROR");	
		return -1;
	};

	fread(bmpHeader,HEADER_LEN,1,fp_in);
	fwrite(bmpHeader,HEADER_LEN,1,fp_out);


	if(NULL==(rgb = (unsigned char*)malloc(WIDTH*HEIGHT*2*1.5*sizeof(unsigned char)))){
		perror("malloc error");
		exit(0);
	};

	fread(yuyv,HEIGHT*WIDTH*2,1,fp_in);
	yuyv2rgb(yuyv,rgb,HEIGHT*WIDTH*2);

	fwrite(rgb,HEIGHT*WIDTH*3,1,fp_out);
	fclose(fp_in);
	fclose(fp_out);
	

	
		

}
