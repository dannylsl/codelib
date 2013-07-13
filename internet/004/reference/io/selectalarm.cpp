#include <cstdio>
#include <sys/select.h>
#include <csignal>
#include <unistd.h>
#include <cerrno>

#include <iostream>
using namespace std;

void sighander(int signo) {
   cout << "The alarm happens" << endl;
}
int main() {

   fd_set rset;
   signal(SIGALRM,sighander);
   FD_ZERO(&rset);
   FD_SET(fileno(stdin),&rset);
   alarm(2);
   FD_ZERO(&rset);
   for(;;) {

      FD_SET(fileno(stdin),&rset);
      if(select(3, &rset, NULL, NULL, NULL) < 0)
      {
         if(errno == EINTR) {
              cout << "EINTR error is returned!" << endl;
              continue;
         }
         else{
              perror("select");
              break;
         }
      }
   }
   return 0;
}
