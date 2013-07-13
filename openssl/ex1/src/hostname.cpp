/* 
 Get the host's name.
 Copyright (C) 1994-1995, Li Suke, School of Software,Peking University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int length = 20;	
    char name[1024] ;
    char *hostname;   
    hostname = name ;
    gethostname(hostname,sizeof(name));
    cout << "The hostname of the machine is "<< hostname;
    return 0;

}
