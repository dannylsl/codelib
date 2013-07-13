#ifndef __YUYV2RGB_H_
#define __YUYV2RGB_H_

/*
 * Usage:
 *	You must malloc rgb before using this function
 *	and  make sure that
 *		rgb_size = 3*yuyv/2
 *		yuyv_size = 4*N
 */	
unsigned char* yuyv2rgb(const unsigned char* yuyv, unsigned char *rgb,int yuyv_size){
	int r,g,b;
	int y,u,v;	
	int rdif,invgdif,bdif;
	int i,j;

	for(i = 0,j=0; i < yuyv_size; i+=4){
		//Pixel 1 
		y = yuyv[i];
		u = yuyv[i+1] - 128; 
		v = yuyv[i+3] - 128;
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
		rgb[j] = b;
		rgb[j+1] = g;
		rgb[j+2] = r;

		//Pixel 2
		y = yuyv[i+2];
		r = y + rdif;
		g = y - invgdif;
		b = y + bdif;
		if(r > 255)		r = 255;
		if(r < 0)		r = 0;
		if(g > 255)		g = 255;
		if(g < 0)		g = 0;
		if(b > 255)		b = 255;
		if(b < 0)		b = 0;
		rgb[j+3] = b;
		rgb[j+4] = g;
		rgb[j+5] = r;
		j+=6;
			
	}
	return rgb;
}


#endif
