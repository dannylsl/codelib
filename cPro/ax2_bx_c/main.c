#include <stdio.h>
#include <math.h>

//#define TYPE double
#define TYPE float

int main(void){
	TYPE x1, x2;	
	TYPE a = 1.0, c = 1.0, b = 1000000.000001 ;
	TYPE d = b*b - 4*a*c;	
	x1 = (-b + sqrtf(d))/(2*a);
	x2 = (-b - sqrtf(d))/(2*a);
	printf("a=%lf\tb=%lf\tc=%lf\n",a,b,c);
	printf("x1=%lf\nx2=%lf\n",x1,x2);
	return 0;
}
