#include <stdio.h>
#include <stdlib.h>

#define FILENAME  "1.bmp"
#define HEADERNAME "bmpheader"
#define HEADER_LEN  72

int main(int argc,char* argv){
	FILE *fp,*fpHeader;
	char bmp_header[HEADER_LEN];

	if(NULL==(fp = fopen(FILENAME,"rb+"))){
		perror("FILENAME OPEN FAILED");				
		exit(0);
	}
	
	if(NULL==(fpHeader = fopen(HEADERNAME,"wb+"))){
		perror("HEADERNAME OPEN FAILED");
		exit(0);
	}

	fread(bmp_header,HEADER_LEN,1,fp);
	fwrite(bmp_header,HEADER_LEN,1,fpHeader);

	fclose(fp);
	fclose(fpHeader);

}
