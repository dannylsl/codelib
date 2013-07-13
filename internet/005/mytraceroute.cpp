/* fileName : mytraceroute.cpp
 * author	: danny lee
 * student	: 1201210660
 * Description:
 *	my trace route with raw socket
 *
 * */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <cstring>
#include <cerrno>
#include <ctime>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

#define BUF_LEN 1024
#define MAX_HOPS 30

#define TIMEOUT				-3
#define ICMP_TIMEOUT		-2
#define PORT_UNREACHABEL	-1

void printErr(const char* errname){
	cerr<<errname<<":"<<strerror(errno)<<endl;
	exit(EXIT_FAILURE);
}

int recvicmp(int sockfd, struct sockaddr_in *hopaddr, unsigned short s_port,unsigned short d_port,struct timeval*tv);

void timesub(struct  timeval *t1, struct timeval *t2)
{
              
   if(t2->tv_usec < t1->tv_usec){
      t2->tv_sec = t2->tv_sec - t1->tv_sec -1 ;
      t2->tv_usec = t2->tv_usec + 1000000 - t1->tv_usec ;
   }else{
      t2->tv_sec = t2->tv_sec - t1->tv_sec;
      t2->tv_usec = t2->tv_usec - t1->tv_usec;
   }
    
} 

void mytrace(struct sockaddr_in target_addr)
{
	int sockfd,recvfd;
	int ttl=0;
	int probe=0;

	struct sockaddr_in udpaddr,local_addr,hopaddr,oldaddr;

	struct timeval t1,t2;

	int code;
	int flag = 0;
	unsigned short s_port,d_port;

	char ip_str[INET_ADDRSTRLEN];

	s_port = (getpid() & 0xffff) | 0x8000;
	d_port = s_port + 200;

	memset(&udpaddr,'\0',sizeof(struct sockaddr_in));
	memset(&local_addr, '\0',sizeof(struct sockaddr_in));

	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	local_addr.sin_port = htons(s_port);

	udpaddr.sin_family = AF_INET;
	udpaddr.sin_addr = target_addr.sin_addr;
	udpaddr.sin_port = htons(d_port);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0){
		printErr("udp error");
	}

	recvfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if(recvfd < 0){
		printErr("recvfd sock_raw");
	}

	if(bind(sockfd, (struct sockaddr*)&local_addr,
				sizeof(struct sockaddr)) == -1){
		printErr("bind error");
	}

	for(ttl = 1; ttl < MAX_HOPS && (flag == 0); ttl++) {
		cout<<setw(2)<<ttl<<"  ";
		//fflush(stdout);

		for(probe = 0; probe < 3; probe++){
			if(setsockopt(sockfd, IPPROTO_IP,IP_TTL, &ttl, sizeof(int)) == -1){
				printErr("setSockoption error");
			}

			gettimeofday(&t1, NULL);

			if(sendto(sockfd, NULL, 0, 0,(struct sockaddr *)&udpaddr,sizeof(struct sockaddr)) == -1){
				printErr("sendto error");
			}

			code = recvicmp(recvfd, &hopaddr, s_port, d_port, &t2);
			alarm(0);

			if(code == TIMEOUT ){
				cout<<" *";	
			}
			
			if(code == PORT_UNREACHABEL){
				flag = 1;	
			}
			if((code == ICMP_TIMEOUT) || flag==1){
				if(oldaddr.sin_addr.s_addr != hopaddr.sin_addr.s_addr){

					cout<<inet_ntop(AF_INET,&(hopaddr.sin_addr),ip_str, INET_ADDRSTRLEN)<<"\t";

					memcpy(&oldaddr, &hopaddr, sizeof(struct sockaddr_in));
				}
				timesub(&t1, &t2);
				cout<<setw(3)<<(t2.tv_sec* 1000.0 + t2.tv_usec /1000.0 ) <<" ms  \t";
			} 
			code = 0;
			//fflush(stdout);
		}
		cout <<endl;
	}
	close(sockfd);
	close(recvfd);
}

void sighandler(int signo){
	return ;
}

int recvicmp(int sockfd, struct sockaddr_in *hopaddr, unsigned short s_port,unsigned short d_port,struct timeval*tv){
	socklen_t socklen;
	char recvbuf[BUF_LEN];
	int recv_len;

	struct iphdr  *ip;
	struct udphdr *udp;
	struct icmp   *icmp;
	int iplen, iplen2;
	
	signal(SIGALRM,sighandler);
	siginterrupt(SIGALRM,1);
	alarm(3);

	while(1){
		socklen = sizeof(struct sockaddr);
		recv_len = recvfrom(sockfd, recvbuf, BUF_LEN,0,(struct sockaddr*)hopaddr,&socklen);

		if(recv_len < 0){
			if(errno == EINTR)
				return TIMEOUT;
			else
				exit(EXIT_FAILURE);
		}

		if(recv_len < 28){
			printErr("error in receiving ip packet");	
		}
		gettimeofday(tv,NULL);

		ip = (struct iphdr*)recvbuf;
		iplen = (ip->ihl) <<2;

		if(iplen < 20)
			printErr("ip header length error");

		icmp = (struct icmp*)(recvbuf + iplen);
		ip   = (struct iphdr*)(recvbuf + iplen + sizeof(struct icmphdr));

		iplen2 = ip->ihl << 2;
		udp = (struct udphdr*)(recvbuf + iplen2+sizeof(struct icmphdr)+iplen2);

		if((ip->protocol == IPPROTO_UDP) &&(ntohs(udp->source) == (s_port)) && (ntohs(udp->dest) == (d_port))){
			if((icmp->icmp_type == ICMP_TIMXCEED) && (icmp->icmp_code == ICMP_TIMXCEED_INTRANS)){
				return ICMP_TIMEOUT;	
			}else if(icmp->icmp_type == ICMP_UNREACH){
				return PORT_UNREACHABEL;
			}	
		}
	}
	return 0;
}

int main(int argc, char *argv[]){
	struct hostent *h;
	struct sockaddr_in target_addr;
	char ip_str[INET_ADDRSTRLEN];
	const char *p;

	if(argc != 2){
		cout << "Usage mytraceroute <hostname>"<<endl;	
		exit(EXIT_FAILURE);
	}

	h = gethostbyname(argv[1]);	
	if(NULL == h)
		printErr("gethostbyname error");
	
	bzero(&target_addr, sizeof(struct sockaddr_in));
	target_addr.sin_addr =*(struct in_addr*)(h->h_addr);
	target_addr.sin_family = AF_INET;

	p = inet_ntop(AF_INET, &target_addr.sin_addr, ip_str, INET_ADDRSTRLEN);
	if(NULL == p)
		printErr("inet_ntop error");

	cout<<"traceroute to "<<argv[1]<<"("<<p<<"),"<<MAX_HOPS<<" hops max,";
	cout<<(sizeof(struct iphdr) + sizeof(struct udphdr))<<" Byte packets"<<endl;

	mytrace(target_addr);
	return 0;
} 
