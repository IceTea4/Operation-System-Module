/* Kestutis Paulikas KTK kespaul */
/* Failas: kespaul_mmap01.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <string.h>

#define SIZE 1048576

int kp_test_openw(const char *name);
int kp_test_close(int fd);
void* kp_test_mmapw( int d, int size );
int kp_test_munamp( void *a, int size );
int kp_test_usemaped( void *a, int size );

int kp_test_openw(const char *name){
   int dskr;
   dskr = open( name, O_RDWR | O_CREAT | O_EXCL, 0640 );
   if( dskr == -1 ){
      perror( name );
      exit( 255 );
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

void* kp_test_mmapw( int d, int size ){
   void *a = NULL;
   lseek( d, size - 1, SEEK_SET );
   write( d, &d , 1 );	/* iraso bile ka i failo gala */
   a = mmap( NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, d, 0 );
   if( a == MAP_FAILED ){
      perror( "mmap failed" );
      abort();
   }
   return a;
}

int kp_test_munamp( void *a, int size ){
   int rv;
   rv = munmap( a, size );
   if( rv != 0 ){
      puts( "munmap failed" );
      abort();
   }
   return 1;
}

int kp_test_usemaped( void *a, int size ){
   memset( a, 0xF0, size );
   return 1;
}

int main( int argc, char * argv[] ){
   int d;
   void *a = NULL;
   printf( "(C) 2013 kestutis Paulikas, %s\n", __FILE__ );
   if( argc != 2 ){
      printf( "Naudojimas:\n %s failas\n", argv[0] );
      exit( 255 );
   }
   d = kp_test_openw( argv[1] );
   a = kp_test_mmapw( d, SIZE );
   kp_test_usemaped( a, SIZE );
   kp_test_munamp( a, SIZE );
   kp_test_close( d );
   return 0;
}
