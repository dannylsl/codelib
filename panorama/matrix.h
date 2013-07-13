#include <iostream>
#include <iomanip>

using namespace std;


class Matrix{
	private:
		int mwidth;
		int mheight;
		unsigned char **mat;
	public:
		Matrix(int width,int height);
		~Matrix();

		Matrix* matrixCat(const Matrix &a);  
		
		int getWidth(){return mwidth;};
		int getHeight(){return mheight;};
		unsigned char** getMat(){return mat;};

		bool init(int value);
		bool loadData(unsigned char data[],int datasize);
		bool setMatVal(int wIndex,int hIndex,unsigned char value);
		void print();
};
