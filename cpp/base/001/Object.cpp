#include <iostream>
#include <cstring>
#include "Object.h"
using namespace std;

Object::Object(const char* name){
	this->_name = new char(strlen(name));
	strcpy(this->_name, name);
	cout<< "Object "<< this->_name <<" constructed" <<endl;
}

Object::Object(Object& o){
	this->_name = new char(strlen(o._name));		
	strcpy(this->_name, o._name);
	cout<<"Copy Construction Called"<<endl;	
}

Object::~Object(){
	cout<<"Oject released"<<endl;
	delete [] this->_name;
}

char* Object::get_obj_name() const{
	return this->_name;
}




