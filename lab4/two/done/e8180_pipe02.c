#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
	int pipefd[2];
	int pipe2fd[2];
	pid_t pid;
	char buffer[BUF_SIZE];

	if (pipe(pipefd) == -1 || pipe(pipe2fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork();

	if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		close(pipefd[1]);
		close(pipe2fd[0]);

		ssize_t n;
		while((n = read(pipefd[0], buffer, BUF_SIZE)) > 0) {
			write(STDOUT_FILENO, buffer, n);
			if (write(pipe2fd[1], buffer, n) < 0) {
				perror("child write");
				break;
			}
		}

		close(pipefd[0]);
		close(pipe2fd[1]);
		exit(EXIT_SUCCESS);
	} else {
		close(pipefd[0]);
		close(pipe2fd[1]);

		int fd = open(argv[1], O_RDONLY);
		if (fd < 0) {
			perror("open");
			close(pipefd[1]);
			close(pipe2fd[0]);
			exit(EXIT_FAILURE);
		}
		
		int fd_out = open("rez", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0) {
			perror("open output");
			close(fd);
			close(pipefd[1]);
			close(pipe2fd[0]);
			exit(EXIT_FAILURE);
		}

		ssize_t n;
		while ((n = read(fd, buffer, BUF_SIZE)) > 0) {
			if (write(pipefd[1], buffer, n) < 0) {
				perror("parent write to child");
				break;
			}
			
			ssize_t m = read(pipe2fd[0], buffer, BUF_SIZE);
			if (m < 0) {
				perror("parent read from child");
				break;
			}
			
			if (write(fd_out, buffer, m) < 0) {
				perror("write to rez file");
				break;
			}
		}

		close(fd);
		close(fd_out);
		close(pipefd[1]);
		close(pipe2fd[0]);
		
		wait(NULL);
		exit(EXIT_SUCCESS);
	}

	return 0;
}
