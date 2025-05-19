/* Kęstutis Paulikas KTK kespaul */
/* Failas: kespaul_open01.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int kp_test_open(const char *name);
int kp_test_close(int fd);
int kp_test_open(const char *name){
   int dskr;
   dskr = open( name, O_RDONLY );
   if( dskr == -1 ){
      perror( name );
      exit(1);
   }
   printf( "dskr = %d\n", dskr );
   return dskr;
}
int kp_test_close(int fd){
   int rv;
   rv = close( fd );
   if( rv != 0 ) perror ( "close() failed" );
   else puts( "closed" );
   return rv;
}
int main( int argc, char *argv[] ){
   int d;
   if( argc != 2 ){
      printf( "Naudojimas:\n %s failas_ar_katalogas\n", argv[0] );
      exit( 255 );
   }
   d = kp_test_open( argv[1] );
   kp_test_close( d );
   kp_test_close( d ); /* turi mesti close klaida */
   return 0;
}
