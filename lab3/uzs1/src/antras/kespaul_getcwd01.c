/* Kęstutis Paulikas KTK kespaul */
/* Failas: kespaul_getcwd01.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int kp_test_getcwd();
int kp_test_getcwd(){
   char *cwd;
   cwd = getcwd( NULL, pathconf( ".", _PC_PATH_MAX) );
   puts( cwd );
   free( cwd );
   return 1;
}
int main(){
   kp_test_getcwd();
   return 0;
}
