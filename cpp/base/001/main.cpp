#include <iostream>
#include "Object.h"
using namespace std;

//print the object information by pass object reference
//This won't call any CONSTRUCTION
void Obj_ref_print(Object &obj){
	cout<<"Object Information: "<< obj.get_obj_name() <<endl;	
}
//If you use an Object as parameter, it will call COPY_CONSTRUCTION to pass 
//Argument to Parameter
void Obj_print(Object obj){
	cout<<"Object Information: "<< obj.get_obj_name() <<endl;	
}

int main(int argv, char* argc[]){
	cout << "Main function" <<endl;
	Object o("O_1");	
	cout<<"**** Object Information *****"<<endl;	
	Obj_print(o);
	cout<<"**** Object Information REFERENCE *****"<<endl;	
	Obj_ref_print(o);

	return 0;
}
