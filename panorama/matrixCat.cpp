/*
 * FileName : matrixCat.cpp
 * Author	: danny lee
 * Email	: dannylsl@pku.edu.cn
 * Date		: 2013-04-28
 * Description:
 */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include "matrix.h"

using namespace std;

#define WIDTH	320
#define HEIGHT  240
#define BUFSIZE	230400 				

int main(int argc, char*argv[]){
	FILE *bmp_in;
	FILE *bmp_out;
	unsigned char bmpdata[BUFSIZE]; 
	unsigned char bmpdataOut[BUFSIZE*6];
	unsigned char **mat;
	unsigned char bmpHeader[54];  
	int i,j;

	char suffix[6][10]={"1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp"};
	char bmpName[6][30];
	char outFile[30];

	if(argc != 2){
		cout<<"Parameters Error"<<endl;
		exit(EXIT_FAILURE);
	}
	

	for(i = 0; i < 6;i++ ){
		sprintf(bmpName[i],"%s_%s",argv[1],suffix[i]);		
		cout<<bmpName[i]<<endl;
	}

	sprintf(outFile,"%s.bmp",argv[1]);
	cout<<"outFileName:"<<outFile<<endl;
	
	if(NULL == (bmp_in = fopen(bmpName[0],"r"))){
		cerr<<"fail to open file:"<<bmpName[0]<<endl;
		return 0;
	}
		
	fseek(bmp_in,54,SEEK_SET);

	Matrix bmpMat(WIDTH*3,HEIGHT);
	Matrix bmp2Cat(WIDTH*3,HEIGHT);

	fread(bmpdata,BUFSIZE,1,bmp_in);
	bmpMat.loadData(bmpdata,BUFSIZE);
	//bmpMat.init(0);
	fclose(bmp_in);

	for(i = 1;i < 6;i++){
		
		if(NULL == (bmp_in = fopen(bmpName[i],"r"))){
			cerr<<"fail to open file:"<<bmpName[i]<<endl;
			return 0;
		}

		fseek(bmp_in,54,SEEK_SET);
		fread(bmpdata,BUFSIZE,1,bmp_in);
	//	bmp2Cat.init(40*i);				
		bmp2Cat.loadData(bmpdata,BUFSIZE);
		bmpMat.matrixCat(bmp2Cat);
		cout<<"Width:"<<bmpMat.getWidth()<<"Height:"<<bmpMat.getHeight()<<endl;
		fclose(bmp_in);
	}

	int width = bmpMat.getWidth();
	int height= bmpMat.getHeight();
	mat = bmpMat.getMat();

	int k=0;
	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			bmpdataOut[k]=mat[i][j];						
			k++;
		}
	}		


	if(NULL == (bmp_out = fopen("paint.bmp","rb"))){
		cerr<<"fail to open file Paint.bmp"<<endl;
		return 0;
	}
	fread(bmpHeader,54,1,bmp_out);
	fclose(bmp_out);

	if(NULL == (bmp_out = fopen(outFile,"wb"))){
		cerr<<"fail to open file CATDATA.BMP"<<endl;
		return 0;
	}

	fwrite(bmpHeader,54,1,bmp_out);
	fwrite(bmpdataOut,BUFSIZE*6,1,bmp_out);
	fclose(bmp_out);
	

/*	
	Matrix a(2,3);
	Matrix b(2,3);
	a.init(50);
	a.print();
	a.setMatVal(1,1,55);
	b.init(49);
	b.print();
	a.matrixCat(b);
	a.print();
*/
};
