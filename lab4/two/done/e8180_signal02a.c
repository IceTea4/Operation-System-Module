#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdlib.h>

static int received_usr1 = 0;
static int received_usr2 = 0;
pid_t child_pid = 0;

void il_catch_USR1( int );       /* signalo apdorojimo f-ja */
void il_catch_USR2(int);
int il_child( void );            /* vaiko proceso veiksmai */
int il_parent( pid_t pid );      /* tevo proceso veiksmai */

int il_child( void ){
   sleep( 1 );
   printf( "        child: my ID = %d\n", getpid() );
   while( 1 ){
      if ( received_usr1 == 1 ){
          printf( "        child: Received signalUSR1 from parent!\n" );
	  system("who");
	  kill(getppid(), SIGUSR2);
          printf( "        child: Sent sigUSR2 to parent, I'm waiting for kill\n" );
          while(1);
      }
   }
   return 0;
}

int il_parent( pid_t pid ){
   printf( "parent: my ID = %d\n", getpid() );
   printf( "parent: my child's ID = %d\n", pid );
   sleep( 3 );
   kill( pid, SIGUSR1 );
   printf( "parent: SignalUSR1 was sent\n" );

   while(1) {
	if (received_usr2 == 1) {
		printf("parent: Received SIGUSR2 from chld\n");
		kill(pid, SIGKILL);
		printf("parent: Killed child process\n");
		sleep(5);
		printf("parent: Job done. Exiting\n");
		break;
	}
   }

   return 0;
}

void il_catch_USR1( int snum ) {
   received_usr1 = 1;
}

void il_catch_USR2(int snum) {
   received_usr2 = 1;
}

int main( int argc, char **arg ){
   pid_t  pid;
   printf( "(C) 2013 Ingrida Lagzdinyte-Budnike, %s\n", __FILE__ );
   signal(SIGUSR1, il_catch_USR1);
   signal(SIGUSR2, il_catch_USR2);
   switch( pid = fork() ){
      case 0:                                         /* fork() grazina 0 vaiko procesui */
         il_child();
         break;
      default:                                        /* fork() grazina vaiko PID tevo procesui */
         il_parent(pid);
         break;
      case -1:                                        /* fork() nepavyko */
         perror("fork");
         exit(1);
   }
   exit(0);
}
