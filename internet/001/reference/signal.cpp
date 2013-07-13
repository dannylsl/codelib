#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int signo)
{
	switch(signo) {
		case SIGUSR1: //处理信号 SIGUSR1
			printf("Parent : catch SIGUSR1n");
		case SIGUSR2: //处理信号 SIGUSR2
			printf("Child : catch SIGUSR2n");
		default:      //本例不支持
			printf("Should not be heren");
			break;
	}
}

int main(void)
{
	pid_t ppid, cpid;
	//为两个信号设置信号处理函数
	if(signal(SIGUSR1, handler) == SIG_ERR) { //设置出错
		perror("Can't set handler for SIGUSR1");
		exit(1);
	}

	if(signal(SIGUSR2, handler) == SIG_ERR) { //设置出错
		perror("Can't set handler for SIGUSR2");
		exit(1);
	}

	ppid = getpid();//得到父进程ID

	if((cpid = fork()) < 0) {
		perror("fail to fork");
		exit(1);
	} else if(cpid == 0) { //子进程
		if(kill(ppid, SIGUSR1) == -1) {
			perror("fail to send signal");
			exit(1);
		}

		while(1);//死循环，等待父进程的信号
	} else {
		sleep(1);//休眠，保证子进程先运行，并且发送SIGUSR1信号

		if(kill(ppid, SIGUSR2) == -1) {
			perror("fail to send signal");
			exit(1);
		}

		printf("kill childn");//输出提示

		if(kill(ppid, SIGKILL) == -1) { //发送SIGKILL信号，杀死子进程
			perror("fail to send signal");
			exit(1);
		}

		if(wait(NULL) ==-1) { //回收子进程状态，避免僵尸进程
			perror("fail to wait");
			exit(1);
		}
	}

	return;
}
