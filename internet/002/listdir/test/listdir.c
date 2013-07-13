#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	DIR *dp;
	struct dirent *ep;
	struct stat fileinfo;

	dp = opendir(".");
	if (dp != NULL) {
		while (ep = readdir(dp)){
			puts(ep->d_name);
			if(strcmp(".",ep->d_name) && strcmp("..",ep->d_name))
				lstat(ep->d_name,&fileinfo);
		}
		closedir(dp);
	}
	return 0;
}

