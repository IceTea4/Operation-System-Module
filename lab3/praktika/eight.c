#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	if (argc != 4) {
		printf("Netinkamas argumentu kiekis\n");
		exit(205);
	}

	int fd;
	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror("Nepavyko atidaryti failo\n");
		abort();
	}

	int N = atoi(argv[2]);
	int M = atoi(argv[3]);

	struct stat st;
	if (stat(argv[1], &st) == -1) {
		perror("Nepavyko stat\n");
		abort();
	}

	if (N > st.st_size) {
		perror("Bloga pozicija\n");
		abort();
	}

	if (lseek(fd, N, SEEK_SET) == -1) {
		perror("Nepavyko lseek\n");
		abort();
	}

	char buffer[M];

	if (read(fd, &buffer, M) == -1) {
		perror("Nepavyko read\n");
		abort();
	}

	//6
	//if (strlen(buffer) != sizeof(buffer)) {
		//perror("Neatitinka ilgis\n");
		//abort();
	//}
	printf("Size: %ld\n", st.st_size);
	if (M > st.st_size - N) {
		perror("Neatitinka ilgis\n");
		abort();
	}

	int fd2;
	if ((fd2 = open("data.bin", O_CREAT | O_WRONLY | O_TRUNC)) == -1) {
		perror("Nepavyko atidaryt data.bin\n");
		abort();
	}

	if (write(fd2, &buffer, M) == -1) {
		perror("Nepavyko irasyti i faila\n");
		abort();
	}

	if (chmod("data.bin", S_IRUSR | S_IWUSR | S_IXUSR | S_IROTH | S_IWOTH | S_IXOTH) == -1) {
		perror("Nepavyko pakeisti teisiu\n");
		abort();
	}

	return 0;
}
