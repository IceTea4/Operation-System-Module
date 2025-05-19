#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
 
int main (){
   int      fd[2];
   pid_t    pid, x;
   int      status;
   printf( "(C) 2013 Nijole Sarafiniene, %s\n", __FILE__ );
   if( pipe( fd ) == -1 ){
      fprintf( stderr, "Nepavyko sukurti programinio kanalo !\n" );
      exit( 1 );
   }
   pid = getpid();
   if( write( fd[1], &pid, sizeof( pid ) ) != sizeof( pid ) ){
      fprintf( stderr, "Klaida rasant" );
      exit( 2 );
   }
   pid = fork();
   if( pid == 0 ){
      sleep( 1 );  
      read( fd[0], &pid, sizeof( pid ) );
      printf ( "(vaikas) Tevo proceso ID: %d\n", pid );
      exit( 1 ); 
   }
   else if( pid == -1 ){ 
      fprintf ( stderr, "Nepavyko sukurti vaiko !\n" );
      exit( 4 );
   }
   else{ 
      printf("(tevas) Mano PID: %d\n", getpid() );
      x = wait( &status );
      return 0;
   }
}
