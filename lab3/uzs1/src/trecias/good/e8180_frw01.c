/* Aistis Jakutonis IFF3/1 e8180 */
/* Failas: e8180_rw01.c */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

FILE *first(const char *filename);
FILE *second(const char *filename);
int third(FILE *fd_read, FILE *fd_write, size_t bytes_to_copy);

FILE *first(const char *filename) {
	FILE *fd = fopen(filename, "rb");
	return fd;
}

FILE *second(const char *filename) {
	FILE *fd = fopen(filename, "wb");
	return fd;
}

int third(FILE *fd_read, FILE *fd_write, size_t bytes_to_copy) {
	char buf[BUFFER_SIZE];
	size_t copied = 0;

	while (copied < bytes_to_copy) {
		size_t bytes_to_read = (bytes_to_copy - copied < BUFFER_SIZE)
					? (bytes_to_copy - copied)
					: BUFFER_SIZE;

		size_t bytes_read = fread(buf, 1, bytes_to_read, fd_read);

		if (bytes_read == 0) {
			if (feof(fd_read)) break;
			if (ferror(fd_read)) {
				perror("Klaida skaitant faila");
				return 1;
			}
		}

		size_t bytes_written = fwrite(buf, 1, bytes_read, fd_write);

		if (bytes_written != bytes_read) {
			perror("Klaida rasant faila");
			return 1;
		}

		copied += bytes_read;
	}

	return 0;
}

int main ( int argc, char * argv[] ) {
	printf( "(C) 2025 Aistis Jakutonis, %s\n", __FILE__ );

	if (argc != 4) {
		fprintf(stderr, "Naudojimas: %s <skaitymo_failas> <rasymo_failas\n", argv[0]);
		return 1;
	}

	FILE *fd_read = first(argv[1]);

	if (!fd_read) {
		perror("Nepavyko atidaryti failo");
		return 1;
	}

	FILE *fd_write = second(argv[2]);

	if (!fd_write) {
		perror("Klaida atidarant/kuriant rasymo faila");
		return 1;
	}

	third(fd_read, fd_write, atoi(argv[3]));

	printf("Darbas baigtas\n");

	fclose(fd_read);
	fclose(fd_write);

	return 0;
}
