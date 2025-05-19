#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

void il_catch_CHLD(int);
void il_catch_ALRM(int);
void il_child(void);
void il_parent(int pid);

void il_child(void) {
    printf("        child: I'm the child\n");
    sleep(3);
    printf("	    child: sending SIGALRM to parent\n");
    kill(getppid(), SIGALRM);
    printf("        child: I'm exiting\n");
    exit(123);
}
void il_parent(int pid) {
    printf("parent: I'm the parent\n");
    sleep(10);
    printf("parent: exiting\n");
}
void il_catch_CHLD(int snum) {
    int pid;
    int status;
    pid = wait(&status);
    sleep(1);
    printf("parent: child process (PID=%d) exited with value %d\n", pid, WEXITSTATUS(status));
}

void il_catch_ALRM(int snum) {
    printf("parent: recieved signal %d (SIGALRM)\n", snum);
}

int main(int argc, char **argv) {
    int pid;                                /* proceso ID */
 
   printf( "(C) 2013 Ingrida Lagzdinyte-Budnike, %s\n", __FILE__ );

    signal(SIGCHLD, il_catch_CHLD);        /* aptikti vaiko proc pasibaigima ir apdoroti */
    signal(SIGALRM, il_catch_ALRM);

    switch (pid = fork()) {
    case 0:                                /* fork() grazina 0 vaiko procesui */
        il_child();
        break;
    default:                                /* fork() grazina vaiko PID tevo procesui */
        il_parent(pid);
        break;
    case -1:                                /* fork() nepavyko */
        perror("fork");
        exit(1);
    }
    exit(0);
}
