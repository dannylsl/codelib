/**
 * FileName	: listdir.cpp
 * Author	: Danny Lee
 * Email	: dannylsl@pku.edu.cn
 * StudentID: 1201210660
 *
 * Description : 
 *	This program is used to achieve the function that 'ls -l' do
 */
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>


using namespace std;

#define MAX_LEN_DIR 255
#define MAX_LEN_NAME 32

int lw=0,uidw=0,gidw=0,sizew=0,tmw=0;
long int total=0;

bool IsHideFile(char fileName[]){
	if(fileName[0] == '.'){
		return true;
	}else{
		return false;
	}
}

void mode2purview(int mode, char purview[]){
	strcpy(purview,"----------\0");

	switch(mode & S_IFMT) {
		case S_IFBLK:  purview[0] = 'b'; break;
		case S_IFCHR:  purview[0] = 'c'; break;
		case S_IFDIR:  purview[0] = 'd'; break;
		case S_IFIFO:  purview[0] = 'p'; break;
		case S_IFLNK:  purview[0] = 'l'; break;
		case S_IFREG:  purview[0] = '-'; break;
		case S_IFSOCK: purview[0] = 's'; break;
		default:   break;
	}

	if(mode & S_IRUSR)  purview[1] = 'r';
	if(mode & S_IWUSR)  purview[2] = 'w';
	if(mode & S_IXUSR)  purview[3] = 'x';

	if(mode & S_IRGRP)  purview[4] = 'r';
	if(mode & S_IWGRP)  purview[5] = 'w';
	if(mode & S_IXGRP)  purview[6] = 'x';

	if(mode & S_IROTH)  purview[7] = 'r';
	if(mode & S_IWOTH)  purview[8] = 'w';
	if(mode & S_IXOTH)  purview[9] = 'x';
}

char* uid2name(uid_t uid){
	struct passwd *pw_ptr;	
	static char numstr[MAX_LEN_NAME];

	if(NULL == (pw_ptr = getpwuid(uid))){
		sprintf(numstr,"%d",uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

char *gid2name(gid_t gid){
	struct group* grp_ptr;
	static char numstr[MAX_LEN_NAME];

	if(NULL == (grp_ptr = getgrgid(gid))){
		sprintf(numstr,"%d",gid);	
		return numstr;
	}else{
		return grp_ptr->gr_name;
	}
}

void detialshow(char * fileName,struct stat *fileinfo){
	char purview[11];	
	struct tm *tm;
	char timestrbuf[30];

	mode2purview(fileinfo->st_mode,purview);

	cout<<purview<<setw(lw+1)<<fileinfo->st_nlink<<setw(uidw+1)<<uid2name(fileinfo->st_uid);
	cout<<setw(gidw+1)<<gid2name(fileinfo->st_gid)<<setw(sizew+1)<<(long)fileinfo->st_size;
	tm = localtime(&(fileinfo->st_ctime));
	strftime(timestrbuf,29,"%b %d %H:%M",tm);
	cout<<setw(13)<<timestrbuf<<" "<<fileName<<endl;

}

int main(int argc, char* argv[]){
	DIR *dp;
	struct dirent **namelist;
	struct stat fileinfo;
	char dirName[MAX_LEN_DIR];
	char wtmp[MAX_LEN_NAME];
	int i,n,j;
	struct tm *tm;
	char timestrbuf[30];
	

	memset(dirName,'\0',MAX_LEN_DIR);

	if(argc >= 3){
		cout<<"Arguments errors"<<endl;
		exit(1);
	}

	if(argc == 1){
		strcpy(dirName,"./");
	}else{
		strcpy(dirName,argv[1]);
		chdir(argv[1]);  //change to argv directory
	}
	n = scandir(dirName,&namelist,0, alphasort);
	if(n < 0){
		cerr << "scandir error";
	}else{
		for(i = 0; i < n; i++){
			if(strcmp(namelist[i]->d_name,".") && strcmp(namelist[i]->d_name,"..") && !IsHideFile(namelist[i]->d_name)){
				if(lstat(namelist[i]->d_name,&fileinfo) != -1){
					memset(wtmp,'\0',MAX_LEN_NAME);
					sprintf(wtmp,"%d",fileinfo.st_nlink);
					lw = (lw < strlen(wtmp))?strlen(wtmp):lw;

					memset(wtmp,'\0',MAX_LEN_NAME);
					sprintf(wtmp,"%s",uid2name(fileinfo.st_uid));
					uidw = (uidw < strlen(wtmp))?strlen(wtmp):uidw;

					memset(wtmp,'\0',MAX_LEN_NAME);
					sprintf(wtmp,"%s",gid2name(fileinfo.st_gid));
					gidw = (gidw < strlen(wtmp))?strlen(wtmp):gidw;

					memset(wtmp,'\0',MAX_LEN_NAME);
					sprintf(wtmp,"%ld",fileinfo.st_size);
					sizew = (sizew < strlen(wtmp))?strlen(wtmp):sizew;

					memset(wtmp,'\0',MAX_LEN_NAME);
					tm = localtime(&(fileinfo.st_ctime));
					strftime(wtmp,29,"%b %d %H:%M",tm);
					tmw = (tmw < strlen(wtmp))?strlen(wtmp):tmw;

					total+=fileinfo.st_blocks;

				}
			}
		}

		cout<<"total:"<<total/2<<endl;
		for(j = 0; j < n; j++){
			if(strcmp(namelist[j]->d_name,".") && strcmp(namelist[j]->d_name,"..") && !IsHideFile(namelist[j]->d_name))
				if(lstat(namelist[j]->d_name,&fileinfo) != -1) 
					detialshow(namelist[j]->d_name,&fileinfo);
			free(namelist[j]);
		}
		free(namelist);
	}

	return 0;

}

