#include <sys/types.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <iostream>

using namespace std;


int main () 
{

  char ip_str[INET_ADDRSTRLEN];
  strcpy(ip_str, "192.168.21.120");
  struct in_addr addr;
  struct in_addr temp_addr;

  in_addr_t s_addr;
  in_addr_t local;
  in_addr_t net;

  int ret_val;
  char *p;

  ret_val = inet_aton(ip_str,&addr);
  if (ret_val == 0){
    perror("inet_aton");
    exit(1);
  }
  p = inet_ntoa (addr);	
  if (p == NULL){
    perror("inet_ntoa");
    exit(1);
  }
  cout << "The ip string is "<<  p << endl;

  if ((s_addr = inet_addr (ip_str)) == INADDR_NONE){
    perror("inet_addr");
    exit(1);
  }
  temp_addr.s_addr = s_addr;
  cout << "inet_addr " << inet_ntoa(temp_addr) << endl;



  if ((s_addr =inet_network (ip_str)) == -1){
    perror("inet_network");
    exit(1);
  }
  
  temp_addr.s_addr = htonl(s_addr);
  cout << "inet_network " << inet_ntoa (temp_addr) << endl;
  
  if ((s_addr = inet_lnaof ( addr)) == -1) {
    perror("inet_lnaof");
    exit(1);
  }
  local = s_addr;
  temp_addr.s_addr = htonl(s_addr);
  cout << "inet_lnaof " <<  inet_ntoa(temp_addr) << endl;

  if ((s_addr = inet_netof (addr)) == -1) {
    perror("inet_netof");
    exit(1);
  }
  net = s_addr;
  temp_addr.s_addr = htonl(s_addr);
  cout << "inet_netof " <<  inet_ntoa(temp_addr) << endl;
  cout << "inet_makeaddr "<< inet_ntoa(inet_makeaddr(net,local)) << endl;
 
  return 0;

}
