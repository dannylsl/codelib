#include <time.h>
#include "v4l2_4arm.h"
//#include "v4l2.h"
#include "yuyv2rgb.h"
#include "motor.h"

v4l2_device vd;

#define BMPHEADER_LEN	54
#define RGB2YUVRATIO	1.5
#define BMPHEADER		"bmpheader320_240" 
#define ZERO			48
#define NAME_LEN		30

// Get time to String
char *get_str_time(char *strTime){
	
	time_t now;
	struct tm *timenow;		
		
	time(&now);
	timenow = localtime(&now);

	sprintf(strTime,"%d%d%d%d%d%d",timenow->tm_year+1900,timenow->tm_mon+1,timenow->tm_mday,
			timenow->tm_hour,timenow->tm_min,timenow->tm_sec);	

	return strTime;
}

// Create FileName from time and no
char *create_file_name(const char*strTime,int no,char*fileName){
	memset(fileName,0,NAME_LEN);
	sprintf(fileName,"%s_%c.bmp",strTime,no+ZERO);		
	return fileName;
}


void main()
{
	int yuyv_len;
	FILE *fp,*fp_bmph;
	unsigned char bmpHeader[BMPHEADER_LEN];
	unsigned char* yuyv;
	unsigned char* rgb;
	char strTime[NAME_LEN],fileName[NAME_LEN];
	char matrixCatCmd[100];
	char bmp2jpgCmd[100];
	int i;

	memset(strTime,0,NAME_LEN);
	memset(matrixCatCmd,0,100);
	memset(bmp2jpgCmd,0,100);
	//Get Current Time
	get_str_time((char*)&strTime);
	printf("%s\n",strTime);

	sprintf(matrixCatCmd,"./matrixCatOnArm %s",strTime);
	printf("%s\n",matrixCatCmd);
	sprintf(bmp2jpgCmd,"./bmp2jpg %s 1920 240",strTime);
	printf("%s\n",matrixCatCmd);

	v4l2_open("/dev/video2",&vd);	
	v4l2_show_support_fmt(&vd);
	v4l2_set_capture_fmt(&vd);
	v4l2_apply_capture_buffer(&vd);
	v4l2_set_capture_buffer(&vd);
////////////////////////
// MOTOR INITIALIZE
	if(init_motor() < 0){
		perror("MOTOR INITIALIZED FAILED!");
		exit(EXIT_FAILURE);
	}
	set_motor_direction(0);
	set_motor_count(400);
	printf("motor initialized!\n");

///////////////////////
	fp_bmph = fopen(BMPHEADER,"r+");
	fread(bmpHeader,BMPHEADER_LEN,1,fp_bmph);

	printf("Start grab image...\n");
	for(i = 0; i < 6;i++){

		v4l2_start_capture(&vd);
		create_file_name((char*)strTime,i+1,(char*)fileName);
		printf("%s\n",fileName);
		sleep(2);

		v4l2_get_frame_yuyv(&vd);
		yuyv_len = v4l2_get_frame_size(&vd);	
		rgb = (unsigned char*)malloc(sizeof(unsigned char)*yuyv_len*RGB2YUVRATIO);
		yuyv = v4l2_get_frame_data(&vd);		
		yuyv2rgb(vd.data,rgb,yuyv_len);

		fp = fopen(fileName,"w+");			

		fwrite(bmpHeader,BMPHEADER_LEN,1,fp);
		fwrite(rgb,yuyv_len*RGB2YUVRATIO,1,fp);

		fclose(fp);
			
		rotate_motor();
		sleep(1);
		v4l2_stop_capture(&vd);	
	}
	
	set_motor_direction(1);
	while(i--){
		rotate_motor();	
	}
///////////////////////		
	fclose(fp_bmph);
	v4l2_release_capture_buffer(&vd);
	v4l2_close(&vd);

	printf("Start Image Cat...\n");
	system(matrixCatCmd);
	printf("Image Cat Done!\n");

	printf("Bmp 2 Jpeg Conversion start...\n");
	system(bmp2jpgCmd);
	printf("Bmp 2 Jpeg Done!\n");

	close_motor();
}
