/* Aistis Jakutonis IFF3/1 e8180 */
/* Failas: e8180_seek01.c */

#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int one(const char *filename);
int two(int fd);
int third(int fd);

int one(const char *filename) {
	int fd = creat(filename, 0644);

	return fd;
}

int two(int fd) {
	int res = lseek(fd, 1024 * 1024, SEEK_SET);

	if (res == -1) {
		perror("Klaida atliekant lseek()");
		return 1;
	}

	return 0;
}

int third(int fd) {
	char c = 'A';

	int res = write(fd, &c, 1);

	if (res == -1) {
		perror("Klaida rasant viena baita");
		return 1;
	}
}

int main ( int argc, char * argv[] ) {
	printf( "(C) 2025 Aistis Jakutonis, %s\n", __FILE__ );

	if (argc < 2) return 1;

	int fd = one(argv[1]);

	if (fd == -1) return 1;

	two(fd);

	third(fd);

	close(fd);

	return 0;
}
