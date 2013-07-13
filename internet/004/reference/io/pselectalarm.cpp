
#include <sys/select.h>
#include <signal.h>
#include <cerrno>
#include <iostream>

using namespace std;

void sighander(int signo){
   cout << "The alarm happens" << endl;
}

int main(void){

   fd_set rset;
   sigset_t newset;
   sigset_t oldset;
   sigset_t zeroset;

   sigemptyset(&newset);
   sigemptyset(&zeroset);
   sigaddset(&newset, SIGALRM);

   signal(SIGALRM, sighander);

   alarm(2);

   FD_ZERO(&rset);

   FD_SET(fileno(stdin),&rset);  

   sigprocmask(SIG_BLOCK, &newset, &oldset);

   if (pselect(3, &rset, NULL, NULL, NULL, &zeroset) < 0)
   {
      if (errno == EINTR)
         cout <<"EINTR error is returned!" << endl;
      else {
         perror("select");
         exit(1);
      }
      
   }
   sigprocmask(SIG_SETMASK, &oldset, NULL);
   return 0;
}
