#include <iostream>
#include <stdio.h>
using namespace std;

int main(void){
	signed char ch;
	cout<<"Input anything you want and Use 'Ctrl-d' or 'Ctrl-z' to stop"<<endl;	
	cin>>ch;
	while(!cin.eof()){
		cout<<"Your Input:" << ch <<endl;		
		cout<<"Wait for your input:";
		cin>>ch;
		cout<<endl;
	}
	cout<<"Loop end since your EOF input" <<endl;

	printf("Get ch by getchar() Ctrl-D or Ctrl-Z to quit\n");
	while((ch=getchar()) != EOF){
		printf("ch=%c\n", ch);
	}
	printf("Loop end since your EOF input\n");
					
	return 0;
}
