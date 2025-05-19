/* Kestutis Paulikas KTK kespaul */
/* Failas: kespaul_nftw01.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ftw.h>
int kp_ftwinfo(const char *p, const struct stat *st, int fl, struct FTW *fbuf);
int kp_ftwinfo(const char *p, const struct stat *st, int fl, struct FTW *fbuf){
   static int cnt = 0;
   puts( p );
   cnt++;
   if( cnt >= 10 ) return cnt;        /* pabandykite uzkomentuoti sita elutę */
   return 0;
}
int main(){
   int rv;
   printf( "(C) 2013 kestutis Paulikas, %s\n", __FILE__ );
   rv = nftw( ".", kp_ftwinfo, 20, 0 );
   if( rv == -1 ){
      perror( "nftw failed" );
      exit( 1 );
   }
   if( rv != 0 ){
      printf( "ntfw fn function returnd %d != 0 -> nftw finished\n", rv );
   }
   return 0;
}
