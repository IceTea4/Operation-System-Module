/* Kestutis Paulikas KTK kespaul */
/* Failas: kespaul_limits02.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>

int kp_change_filelimit( int nslimit, int nhlimit );
int kp_test_filelimit( const char *fn );

int kp_change_filelimit( int nslimit, int nhlimit ){
   struct rlimit rl;
   getrlimit( RLIMIT_NOFILE, &rl );
   printf( "RLIMIT_NOFILE %ld (soft) %ld (hard)\n", rl.rlim_cur, rl.rlim_max );
   rl.rlim_cur = nslimit;
   rl.rlim_max = nhlimit;
   setrlimit( RLIMIT_NOFILE, &rl );
   getrlimit( RLIMIT_NOFILE, &rl );
   printf( "RLIMIT_NOFILE %ld (soft) %ld (hard)\n", rl.rlim_cur, rl.rlim_max );
   return 1;
}

int kp_test_filelimit( const char *fn ){
   int n;
   for( n = 0; -1 != open( fn, O_RDONLY ); n++ );
   printf( "Can open %d files\n", n );
   return 1;
}

int main( int argc, char *argv[] ){
   printf( "(C) 2013 kestutis Paulikas, %s\n", __FILE__ );
   kp_change_filelimit( 20, 100 );
   kp_test_filelimit( argv[0] );
   return 0;
}
