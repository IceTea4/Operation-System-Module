/* Aistis Jakutonis IFF3/1 e8180 */
/* Failas: e8180_rw01.c */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int first(const char *filename);
int second(const char *filename);
int third(int fd_read, int fd_write, size_t bytes_to_copy);

int first(const char *filename) {
	int fd = open(filename, O_RDONLY);
	return fd;
}

int second(const char *filename) {
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return fd;
}

int third(int fd_read, int fd_write, size_t bytes_to_copy) {
	char buf[BUFFER_SIZE];
	size_t copied = 0;
	ssize_t bytes_read, bytes_to_read;

	while (copied < bytes_to_copy) {
		if (bytes_to_copy - copied < BUFFER_SIZE) {
			bytes_to_read = bytes_to_copy - copied;
		} else {
			bytes_to_read = BUFFER_SIZE;
		}

		bytes_read = read(fd_read, buf, bytes_to_read);

		if (bytes_read == 0) break;
		if (bytes_read < 0) {
			perror("Klaida skaitant faila");
			break;
		}

		ssize_t bytes_written = write(fd_write, buf, bytes_read);

		if (bytes_written < 0) {
			perror("Klaida rasant i faila");
			break;
		}

		copied += bytes_read;
	}
}

int main ( int argc, char * argv[] ) {
	printf( "(C) 2025 Aistis Jakutonis, %s\n", __FILE__ );

	if (argc != 4) {
		fprintf(stderr, "Naudojimas: %s <skaitymo_failas> <rasymo_failas\n", argv[0]);
		return 1;
	}

	int fd_read = first(argv[1]);

	if (fd_read == -1) {
		perror("Nepavyko atidaryti failo");
		return 1;
	}

	int fd_write = second(argv[2]);

	if (fd_write == -1) {
		perror("Klaida atidarant/kuriant rasymo faila");
		return 1;
	}

	third(fd_read, fd_write, atoi(argv[3]));

	printf("Darbas baigtas\n");

	close(fd_read);
	close(fd_write);

	return 0;
}
