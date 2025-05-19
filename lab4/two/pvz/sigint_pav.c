#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void il_catch_INT(int);
void il_catch_INT(int snum) {
   printf("Caught signal %d, coming out...\n", snum);
   exit(1);
}
int main(int argc, char **argv) {
   printf( "(C) 2013 Ingrida Lagzdinyte-Budnike, %s\n", __FILE__ );
   signal(SIGINT, il_catch_INT);
   while(1) 
   {
      printf("Going to sleep for a second...\n");
      sleep(1);
   }
   return(0);
}
