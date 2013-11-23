#ifndef __MYCLASS_H
#define __MYCLASS_H

class MyClass{
public:
	MyClass(int value);
	const int myValue();
	bool operator< (const MyClass& other);
private:
	int _value;
}

#endif
