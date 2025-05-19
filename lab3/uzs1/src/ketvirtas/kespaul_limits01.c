/* Kęstutis Paulikas KTK kespaul */
/* Failas: kespaul_limits01.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int kp_memsize();

int kp_memsize(){
   long pagesize, pages;
   pagesize = sysconf( _SC_PAGESIZE );
   pages = sysconf( _SC_PHYS_PAGES );
   printf( "System:\n\tpage size: %ld\n\tpages: %ld\n", pagesize, pages );
   printf( "Total system RAM: %.1f MB\n", (double)pagesize * pages / 1024 / 1024 );
   return 1;
}

int main(){
   printf( "(C) 2013 kestutis Paulikas, %s\n", __FILE__ );
   kp_memsize();
   return 0;
}
