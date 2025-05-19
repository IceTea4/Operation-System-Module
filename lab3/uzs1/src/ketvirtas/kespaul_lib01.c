/* Kestutis Paulikas KTK kespaul */
/* Failas: kespaul_lib01.c */

#include <stdio.h>
#include "kespaul_lib01.h"

double kespaul_libvar01;

int kespaul_libfunc01( const char *s ){
   printf( "Dynamic library for testing, %s\n", __FILE__ );
   printf( "\tparameter: \"%s\"\n", s );
   printf( "\tlib variable = %f\n", kespaul_libvar01 );
   return 0;
}
