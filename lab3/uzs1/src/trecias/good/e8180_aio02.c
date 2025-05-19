/* Aistis Jakutonis IFF3/1 e8180 */
/* Failas: e8180_aio02.c */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <aio.h>
#include <string.h>

#define BUFFLEN 1048576

int main () {
	printf( "(C) 2025 Aistis Jakutonis, %s\n", __FILE__ );

	const char *filename = "/dev/random";

	int fd = open(filename, O_RDONLY);

	if (fd == -1) {
		perror(filename);
		return 1;
	}

	struct aiocb aior;
	char buffer[BUFFLEN];
	size_t total = 0;

	while (total < BUFFLEN) {
		memset(&aior, 0, sizeof(struct aiocb));

		aior.aio_fildes = fd;
		aior.aio_buf = buffer + total;
		aior.aio_nbytes = BUFFLEN - total;
		aior.aio_offset = 0;

		if (aio_read(&aior) == -1) {
			perror("aio_read klaida");
			close(fd);
			return 1;
		}

		const struct aiocb *aiolist[] = { &aior };
		if (aio_suspend(aiolist, 1, NULL) == -1) {
			perror("aio_suspend klaida");
			close(fd);
			return 1;
		}

		ssize_t bytes = aio_return(&aior);
		if (bytes <= 0) {
			fprintf(stderr, "Klaida arba failo pabaiga\n");
			break;
		}

		total += bytes;
	}

	close(fd);
	return 0;
}
