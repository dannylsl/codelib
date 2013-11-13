#include <iostream>
using namespace std;

typedef const int* IteratorType;

//prototype of the algorithm
//IteratorType find(IteratorType begin, IteratorType end, const int& value) ;

template<class IteratorType, class T>
IteratorType find(IteratorType begin, IteratorType end, const T& value){
	cout << "IteratorType template called" <<endl;
	while(begin != end && *begin != value)
		++begin;
	return begin;
}

int main() {
	const int Count = 100;
	int aContainer[Count];

	IteratorType begin = aContainer;
	IteratorType end = aContainer + Count;

	for(int i = 0; i < Count; ++i)
		aContainer[i] = 2 * i;

	int Number = 0;
	while(Number != -1) {
		cout << "enter required Number (-1 == end):";
		cin >> Number;

		if(Number != -1) {
			IteratorType position = find(begin, end, Number);
			if(position != end) 
				cout << "Found at position: " << (position - begin) << endl;
			else
				cout << Number << " not found!" << endl;
		}
	}
}

//IteratorType find(IteratorType begin, IteratorType end, const int& value) {
//	while(begin != end && *begin != value)
//		++begin;
//	return begin;
//}

