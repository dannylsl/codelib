#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEIGHT	240
#define WIDTH	320

#define HEADER_LEN 54
#define YUYVFILE	"yuyv.bmp"
#define RGBFILE		"rgb.bmp"
#define RGBFILE2	"rgb_int.bmp"

int main(){
		
	FILE *fp_yuv,*fp_rgb,*fp_rgb2;		
	unsigned char yuyv[4];	
	unsigned char rgb[3];
	int r,g,b,y,u,v;
	int rdif,invgdif,bdif;
	unsigned char bmpHeader[HEADER_LEN];
	int i;

	if(NULL == (fp_yuv = fopen(YUYVFILE,"rb+"))){
		perror("YUYVFILE OPEN FAILED");
		exit(0);
	}
	if(NULL == (fp_rgb = fopen(RGBFILE,"w"))){
		perror("RGBFILE OPEN FAILED");
		exit(0);
	}
	if(NULL == (fp_rgb2 = fopen(RGBFILE2,"w"))){
		perror("RGBFILE2 OPEN FAILED");
		exit(0);
	}

//	fseek(fp_yuv, HEADER_LEN, SEEK_SET);
	fread(bmpHeader,HEADER_LEN,1,fp_yuv);
	fwrite(bmpHeader,HEADER_LEN,1,fp_rgb);
	fwrite(bmpHeader,HEADER_LEN,1,fp_rgb2);

	
	for(i=0;i<38400;i++){
		memset(yuyv,0,4);
		fread(yuyv,4,1,fp_yuv);
	//	printf("Y0:%d,U0:%d,Y1:%d,V0:%d\n",yuyv[0],yuyv[1],yuyv[2],yuyv[3]);
	//
/*
*/				
		memset(rgb,0,3);
		y = yuyv[0];
		u = yuyv[1]-128;
		v = yuyv[3]-128;
		rdif	= v+((v*103)>>8);
		invgdif = ((u*88)>>8)+((v*183)>>8);
		bdif	= u+((u*198)>>8);
		r = y + rdif;
		g = y - invgdif;
		b = y + bdif;
		if(r > 255)		r = 255;
		if(r < 0)		r = 0;
		if(g > 255)		g = 255;
		if(g < 0)		g = 0;
		if(b > 255)		b = 255;
		if(b < 0)		b = 0;
		rgb[2] = r;
		rgb[1] = g;
		rgb[0] = b;
		fwrite(rgb,3,1,fp_rgb2);
				
		memset(rgb,0,3);
		y = yuyv[2];
		rdif	= v+((v*103)>>8);
		invgdif = ((u*88)>>8)+((v*183)>>8);
		bdif	= u+((u*198)>>8);
		r = y + rdif;
		g = y - invgdif;
		b = y + bdif;
		if(r > 255)		r = 255;
		if(r < 0)		r = 0;
		if(g > 255)		g = 255;
		if(g < 0)		g = 0;
		if(b > 255)		b = 255;
		if(b < 0)		b = 0;
		rgb[2] = r;
		rgb[1] = g;
		rgb[0] = b;
		fwrite(rgb,3,1,fp_rgb2);
		memset(rgb,0,3);

		b = yuyv[0]+1.779*(yuyv[1]-128); //B		
		//rgb[2] = (b>255)?255:b;
		if(b > 255) b = 255;
		if(b < 0  ) b = 0;
		rgb[2] = r;

		g = yuyv[0]-0.3455*(yuyv[1]-128)-0.7169*(yuyv[3]-128); //G		
		//rgb[1] = (g<0)?0:g;
		if(g > 255) g = 255;
		if(g < 0  ) g = 0;
		rgb[1] = g;
		r = yuyv[0]+1.4075*(yuyv[3]-128); //R		
		//rgb[0] = (r>255)?255:r;
		if(r > 255) r = 255;
		if(r < 0  ) r = 0;
		rgb[0] = b;
		fwrite(rgb,3,1,fp_rgb);
//		printf("B0:%d\tG0:%d\tR0:%d\n",rgb[2],rgb[1],rgb[0]);

		memset(rgb,0,3);
		b = yuyv[2]+1.779*(yuyv[1]-128); //B		
	//	rgb[2] = (b>255)?255:b;
		if(b > 255) b = 255;
		if(b < 0  ) b = 0;
		rgb[2] = r;
		g = yuyv[2]-0.3455*(yuyv[1]-128)-0.7169*(yuyv[3]-128); //G		
	//	rgb[1] = (g<0)?0:g;
		if(g > 255) g = 255;
		if(g < 0  ) g = 0;
		rgb[1] = g;
		r = yuyv[2]+1.4075*(yuyv[3]-128); //R		
	//	rgb[0] = (r>255)?255:r;
		if(r > 255) r = 255;
		if(r < 0  ) r = 0;
		rgb[0] = b;
		fwrite(rgb,3,1,fp_rgb);
//		printf("B0:%d\tG0:%d\tR0:%d\n",rgb[2],rgb[1],rgb[0]);
	}
	
	fclose(fp_yuv);
	fclose(fp_rgb);
	fclose(fp_rgb2);
	
}
