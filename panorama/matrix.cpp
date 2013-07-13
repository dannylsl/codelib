#include "matrix.h"

Matrix::Matrix(int width,int height){
	cout<<"creating matrix"<<width<<height<<endl;
	try{
		mat=new unsigned char*[height];
		for(int i = 0; i < height; i++)
			mat[i] = new unsigned char[width];

	}catch(char*&m){
		cout<<"errno"<<endl;	
	}

	mwidth  = width;
	mheight = height;
	cout<<"matrix created h:"<<mheight<<"w:"<<mwidth<<endl;
};


Matrix* Matrix::matrixCat(const Matrix &a){  
	int nWidth,nHeight;  //new width & height
	int i,j;
	unsigned char **tmp;

	if(this->mheight != a.mheight){
		cerr<<"The matrixs must have the same width!"<<endl;	
		return 0;
	}

	nWidth = this->mwidth + a.mwidth;
	nHeight= this->mheight+ a.mheight;
	try{
		tmp = new unsigned char*[nHeight];
		for(i = 0; i < nHeight; i++){
			tmp[i] = new unsigned char[nWidth];
		}

		for(i = 0; i < mheight; i++){
			for(j = 0; j < mwidth; j++){
				tmp[i][j] = mat[i][j];
			}
		}

		for(i = 0; i < mheight; i++){
			delete [] mat[i];	
		}
		delete [] mat;

		mat = tmp;

		for(i = 0; i < a.mheight; i++)
			for(j = 0; j < a.mwidth; j++)
				mat[i][j+mwidth] = a.mat[i][j];		
		this->mwidth = nWidth;
		
	}catch(...){
		cerr<<"matrixCat failed"<<endl;	
		return 0;
	}
	return this;
}

bool Matrix::init(int value){
	cout<<"matrix Initialized"<<endl;	
	try{
		for(int i=0; i < mheight; i++){
			for(int j = 0; j < mwidth; j++){
				this->mat[i][j] = value;	
			}
		}
	}catch(...){
		cerr<<"matrix Initialize failed"<<endl;
		return false;
	}
	return true;
}


bool Matrix::loadData(unsigned char data[],int datasize){
	int i,j;		
	int rows,lastcol;

	if(datasize > mwidth*mheight){
		cerr<<"can not load all data"<<endl;	
		return false;
	}

	rows = datasize/mwidth;
	lastcol = datasize % mwidth;

	for( i = 0; i < rows; i++){
		if( i == rows-1 ){
			for(j = 0; j < lastcol; j++){
				this->mat[i][j] = data[i*mwidth+j];
			}
		}else{
			for(j = 0; j < mwidth; j++){
				this->mat[i][j] = data[i*mwidth+j]; 			
			}
		}
	} //load data

	return true;
	

}

bool Matrix::setMatVal(int wIndex,int hIndex,unsigned char value){
	if(wIndex+1 > this->mwidth || hIndex+1 > this->mheight){
		cerr<<"The position ("<<wIndex<<","<<hIndex<<") is out of range"<<endl;		
		return false;
	}
	try{
		this->mat[hIndex][wIndex] = value;	
	}catch(...){
		cerr<<"setMatVal failed! wIndex:"<<wIndex<<" hIndex:"<<hIndex<<endl;
		return false;
	}
	return true; 
};

void Matrix::print(){
	for(int i = 0; i < mheight; i++){
		cout << endl;
		for(int j = 0; j < mwidth; j++){
			cout<<setw(4)<<mat[i][j];	
		}
	}	
	cout<<endl;
}

Matrix::~Matrix(){

	for(int i = 0;i<mheight;i++)
		delete []mat[i];
	delete []mat;
	/*	
	*/
};
