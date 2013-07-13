#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

void sighandler(int signum){
	time_t rawtime;
	struct tm* st;

	if(signum == SIGUSR1){
		time(&rawtime);
		st = localtime(&rawtime);	
		cout<<"ParentThread:SIGUSR1 CATCHED\t CURRNT TIME:"<<asctime(st)<<endl;
	}else if(signum == SIGUSR2){
		cout<<"ParentThread:SIGUSR2 CATCHED"<<endl;
		exit(1);
	}
}

int main(){
	pid_t ppid,pid;
	int i;

	if( signal(SIGUSR1,sighandler) == SIG_ERR ){
		cout<<"Can not Set handle for SIGUSR1"<<endl;
		exit(1);
	}
	if( signal(SIGUSR2,sighandler) == SIG_ERR ){
		cout<<"Can not Set handle for SIGUSR2"<<endl;
		exit(1);
	}
		
	ppid = getpid();
	cout<<"fork Pid"<<pid<<endl;

	pid = fork();
	if(pid==0){
		for(i=0;i<5;i++){
			kill(ppid,SIGUSR1);
			cout<<"FORKTHREAD:Sent SIGUSR1 to Parent Thread"<<endl;
			sleep(1);
		}
		kill(ppid,SIGUSR2);
		cout<<"FORKTHREAD:Sent SIGUSR2 to Parent Thread"<<endl;
	}else if(pid < 0){
		cout<<"fork error"<<endl;
		exit(1);
	}
	while(1);
}
