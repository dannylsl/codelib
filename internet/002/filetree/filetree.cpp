/**
 * FileName	: filetree.cpp
 * Author	: Danny Lee
 * Email	: dannylsl@pku.edu.cn
 * StudentID: 1201210660
 *
 * Description : 
 *	This program is used to achieve the function that "tree" do 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <iomanip>
#include <cerrno>

using namespace std;

#define MAX_LEN_DIR  255
#define MAX_LEN_NAME 32

int fileCnt=0,dirCnt=0;

bool IsHideFile(char fileName[]){
	if(fileName[0] == '.'){
		return true;
	}else{
		return false;
	}
}

void printfile(char*fileName,int depth,char* prefix){
	/*		
			while(depth--){
			cout<<"|  ";
			}
			*/
	cout<<prefix;
	cout<<"|--"<<fileName<<endl;
}

void showlist( char dirName[],int depth,char* prefix,bool isLastDir){
	struct dirent **namelist;
	struct stat fileinfo;
	int i,n;
	char symbol;
	char dirtmp[MAX_LEN_DIR];
	char archtree[MAX_LEN_DIR];
	bool lastdir = false;

	memset(dirtmp,'\0',MAX_LEN_DIR);
	memset(archtree,'\0',MAX_LEN_DIR);
	if(depth > 0)
		strcat(archtree,prefix);

	//cout<<"depth:"<<depth<<endl;

	n = scandir(dirName,&namelist,0,alphasort);

	if(n < 0){
		cerr << "scandir error:["<<dirName<<"] "<<strerror(errno)<<endl;
		exit(EXIT_FAILURE);
	}else{

		for(i = 0; i < n;i++){
			if(depth>0 && isLastDir == false){
				archtree[(depth-1)*3  ] = '|';
				archtree[(depth-1)*3+1] = ' ';
				archtree[(depth-1)*3+2] = ' ';
			}else if(depth > 0 && isLastDir == true){
				archtree[(depth-1)*3  ] = ' ';
				archtree[(depth-1)*3+1] = ' ';
				archtree[(depth-1)*3+2] = ' ';
			}
			if(strcmp(namelist[i]->d_name,".") && strcmp(namelist[i]->d_name,"..") && !IsHideFile(namelist[i]->d_name)){
				symbol = namelist[i]->d_type;
				if( symbol != DT_DIR){

					printfile(namelist[i]->d_name,depth,archtree);
					fileCnt++;
				}
				else if( symbol == DT_DIR){
					dirCnt++;
					printfile(namelist[i]->d_name,depth,archtree);
					if(i == (n-1)){
						lastdir = true;
						archtree[depth*3+1] = ' ';
						archtree[depth*3+2] = ' ';
						archtree[depth*3+3] = ' ';

						//cout <<lastdir<<endl;
					}else{
						lastdir = false;	
					}
					//	cout<<archtree<<namelist[i]->d_name<<endl;

					strcpy(dirtmp,dirName);
					strcat(dirName,"/");
					showlist(strcat(dirName,namelist[i]->d_name),depth+1,archtree,lastdir);
					memset(dirName,'\0',MAX_LEN_DIR);
					strcpy(dirName,dirtmp);
				}
			}
			free(namelist[i]);
		}
		free(namelist);
	}
}

int main(int argc, char* argv[]){
	DIR *dp;
	struct stat fileinfo;
	char dirName[MAX_LEN_DIR];

	memset(dirName,'\0',MAX_LEN_DIR);

	if(argc >= 3){
		cerr<<"Arguments errors"<<endl;
		exit(1);
	}

	if(argc == 1){
		strcpy(dirName,"./");	
	}else{
		strcpy(dirName,argv[1]);
	}
	cout<<dirName<<endl;
	showlist(dirName,0,(char*)"",false);

	cout << endl << dirCnt << " directory," << fileCnt <<" files"<<endl;
	return 0;	
}

