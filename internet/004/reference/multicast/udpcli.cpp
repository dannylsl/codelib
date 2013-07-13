// Attention: 
//
//	This file is just the modified version of the source code of
//	the chapter "Advanced UDP Sockets" of UNIX Network Programming 
//	Volume1,Third Edition: The Sockets Networking API.
//	So, thank W.Richard Stevens!
//
//	I just put all the source code together, hope it is helpful
//	for your programming practice.
//

#include <sys/types.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <csignal>

#include <csetjmp>
#include <cerrno>
#include <cstdlib>

#include <iostream>


#include "udpr.h"

#define  MAX_BUF_SIZE 1024
#define RTT_RTOCALC(ptr) ((ptr)->rtt_srtt + (4.0 * (ptr)->rtt_rttvar))


static struct rtt_info rttinfo;
static int rttinit = 0;
static struct msghdr msgsend, msgrecv;  // assumed init to 0 

static struct hdr {
     unsigned int seq;               // sequence # 
     unsigned int ts;                // timestamp when sent 
} sendhdr, recvhdr;

static void sig_alrm(int signo);
static sigjmp_buf jmpbuf;



using namespace std;


int main (int argc, char *argv[])
{
	int sockfd;
	int n;
	int ret_val;

	struct sockaddr_in servaddr;
	char sendbuf[MAX_BUF_SIZE];
	char recvbuf[MAX_BUF_SIZE];

	if (argc != 3) {
		cout << "usage: udpcli <ipaddress> <port>" << endl;
		exit(1);
	}
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
         
        ret_val = inet_pton(AF_INET,argv[1], &servaddr.sin_addr);
        if (ret_val <=0 ) {
		perror("inet_pton");
		exit(1);
	}

	sockfd = socket (AF_INET,SOCK_DGRAM,0);
	if (sockfd < 0){
		perror("socket");
		exit(1);
	}
	while(fgets(sendbuf,MAX_BUF_SIZE,stdin)!= NULL) {

		n = udp_send_recv(sockfd,
                                  sendbuf,
                                  strlen(sendbuf),
				  recvbuf,
                                  MAX_BUF_SIZE,
				  (struct sockaddr *)&servaddr,
				  sizeof(servaddr));
		if (n > 0) {
			recvbuf[n] = '\0';
			fputs(recvbuf,stdout);
		}
	}

	exit (0);
}

int udp_send_recv (int fd,
                   const void *outbuff,
                   int outbytes,
                   void *inbuff,
                   int inbytes,
                   const struct sockaddr *destaddr,
                   int destlen)
{
	
       int n;
       struct iovec iovsend[2], iovrecv[2];

       if (rttinit == 0) {
           rtt_init(&rttinfo);     // first time we're called 
           rttinit = 1;
       }

       sendhdr.seq++;
       msgsend.msg_name = (void *)destaddr;
       msgsend.msg_namelen = destlen;
       msgsend.msg_iov = iovsend;
       msgsend.msg_iovlen = 2;

       iovsend[0].iov_base = &sendhdr;
       iovsend[0].iov_len = sizeof(struct hdr);
       iovsend[1].iov_base = (void *)outbuff;
       iovsend[1].iov_len = outbytes;

       msgrecv.msg_name = NULL;
       msgrecv.msg_namelen = 0;
       msgrecv.msg_iov = iovrecv;
       msgrecv.msg_iovlen = 2;

       iovrecv[0].iov_base = &recvhdr;
       iovrecv[0].iov_len = sizeof(struct hdr);
       iovrecv[1].iov_base = inbuff;
       iovrecv[1].iov_len = inbytes;

       signal(SIGALRM, sig_alrm);

       rtt_newpack(&rttinfo);      // initialize for this packet 

    sendagain:

      sendhdr.ts = rtt_ts(&rttinfo);

#if 0

        struct iovec {
             void *iov_base;   /* Starting address */
             size_t iov_len;   /* Number of bytes */
        };

        struct msghdr {
                  void         * msg_name;     /* optional address */
                  socklen_t    msg_namelen;    /* size of address */
                  struct iovec * msg_iov;      /* scatter/gather array */
                  size_t       msg_iovlen;     /* # elements in msg_iov */
                  void         * msg_control;  /* ancillary data, see below */
                  socklen_t    msg_controllen; /* ancillary data buffer len */
                  int          msg_flags;      /* flags on received message */
              };
#endif

      n = sendmsg(fd, &msgsend, 0);

      if (n < 0) {
           perror("sendmsg");
           exit(1);
      }
      cout << "sent " << n << " bytes information" << endl;
      cout << "seq is " << sendhdr.seq << endl;
      cout << "ts is " << sendhdr.ts << endl;
      cout << "rttinfo.rto is " << rttinfo.rtt_rto << endl;
      alarm(rtt_start(&rttinfo)); // calc timeout value & start timer 

      if (sigsetjmp(jmpbuf, 1) != 0) {
          if (rtt_timeout(&rttinfo) < 0) {
              cout << "udp_send_recv: no response from server, giving up" << endl;
              rttinit = 0;        // reinit in case we're called again 
              errno = ETIMEDOUT;
              return -1;
          }
          goto sendagain;
      }

      do {
          n = recvmsg(fd, &msgrecv, 0);
          if (n < 0){
             perror("recvmsg");
             exit(1);
	  }
      } while (n < sizeof(struct hdr) || recvhdr.seq != sendhdr.seq);

      alarm(0); // stop SIGALRM timer 
      // calculate & store new RTT estimator values 
      rtt_stop(&rttinfo, rtt_ts(&rttinfo) - recvhdr.ts);

      return (n - sizeof(struct hdr));    // return size of received datagram 
}

static void sig_alrm(int signo)
{
     siglongjmp(jmpbuf, 1);
}

static float rtt_minmax(float rto)
{
     if (rto < RTT_RXTMIN)
         rto = RTT_RXTMIN;
     else if (rto > RTT_RXTMAX)
         rto = RTT_RXTMAX;
     return (rto);
}

void rtt_init(struct rtt_info *ptr)
{
     struct timeval tv;

     gettimeofday(&tv, NULL);
     ptr->rtt_base = tv.tv_sec;   // # sec since 1/1/1970 at start 

     ptr->rtt_rtt = 0;
     ptr->rtt_srtt = 0;
     ptr->rtt_rttvar = 0.75;
     ptr->rtt_rto = rtt_minmax(RTT_RTOCALC(ptr));
     // first RTO at (srtt + (4 * rttvar)) = 3 seconds 
}
unsigned int rtt_ts(struct rtt_info *ptr)
{
     unsigned int ts;
     struct timeval tv;

     gettimeofday(&tv, NULL);
     ts = ((tv.tv_sec - ptr->rtt_base) * 1000) + (tv. tv_usec / 1000);
     return (ts);
}

void rtt_newpack(struct rtt_info *ptr)
{
     ptr->rtt_nrexmt = 0;
}

int rtt_start(struct rtt_info *ptr)
{
     return ((int) (ptr->rtt_rto + 0.5));    // round float to int 
     // return value can be used as: alarm(rtt_start(&foo)) */
}
void rtt_stop(struct rtt_info *ptr, uint32_t ms)
{
     double  delta;

     ptr->rtt_rtt = ms / 1000.0; // measured RTT in seconds 

     //
     // Update our estimators of RTT and mean deviation of RTT.
     // See Jacobson's SIGCOMM '88 paper, Appendix A, for the details.
     // We use floating point here for simplicity.
     //

     delta = ptr->rtt_rtt - ptr->rtt_srtt;
     ptr->rtt_srtt += delta / 8; // g = 1/8 

     if (delta < 0.0)
         delta = -delta;         // |delta| 

     ptr->rtt_rttvar += (delta - ptr->rtt_rttvar) / 4; // h = 1/4 

     ptr->rtt_rto = rtt_minmax(RTT_RTOCALC(ptr));
}

int rtt_timeout(struct rtt_info *ptr)
{
     ptr->rtt_rto *= 2;          // next RTO 

     if (++ptr->rtt_nrexmt > RTT_MAXNREXMT)
           return (-1);            // time to give up for this packet
       return (0);
}

