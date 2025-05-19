int N;
int firstBiggerThan4KB(const char *p, const struct stat *st, int fl, struct FTW *fbuf);
int tryToMapFile(const char *p, const struct stat *st, int N);

int tryToMapFile(const char *p, const struct stat *st, int N){
        int fd = open(p, O_RDWR);
        if (fd == -1) {
                perror("Nepavyko atidaryti failo\n");
                return -1;
        }

	char buffer[10];
        lseek(fd, 0, SEEK_SET);
        if (read(fd, buffer, 10) != 10) {
                perror("Nepavyko nuskaityt pirmu 10 baitu\n");
                close(fd);
                return 1;
        }

        lseek(fd, st->st_size + 10, SEEK_SET);
        if(write(fd, buffer, 10) != 10) {
                perror("Nepavyko irasyti 10 baitu\n");
                close(fd);
                return 1;
        }

	void *mapped = mmap(NULL, st->st_size + 10, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, >
        if (mapped == MAP_FAILED) {
                perror("Nepavyko primapinti failo\n");
                close(fd);
                return -1;
        }

	printf("Failas primapintas ir papildytas baitais\n", p);

        if (N >= 0 && N < st->st_size + 10) {
                unsigned char value = *((unsigned char *)mapped + N);
                printf("N=%d baito reiksme: %u\n", N, value);
        }

        munmap(mapped, st->st_size + 10);
        close(fd);
        return 0;
}

int firstBiggerThan4KB(const char *p, const struct stat *st, int fl, struct FTW *fbuf) {
        if (fl == FTW_F) {
                if (st->st_size > 4096) {
                        printf("Rastas tinkamo dydzio failas\n");

                        tryToMapFile(p, st, N);

                        return 1;
                }
        }
}

int main(int argc, char *argv[]){
        printf( "(C) Aistis Jakutonis, %s\n", __FILE__ );

        if (argc != 3) {
                printf("Netinkamas argumentu skaicius\n");
                exit(1);
        }

        int N = atoi(argv[2]);
        if (N < 0) {
                printf("Skaicius turi buti teigiamas ir sveikas\n");
                exit(1);
        }

        int dskr;
        dskr = open(argv[1], O_RDONLY | O_DIRECTORY);
        if (dskr == -1) {
                perror(argv[1]);
                exit(1);
        }
        close(dskr);

        int find;
        find = nftw(argv[1], firstBiggerThan4KB, 20, 0);
        if (find == -1) {
                perror("nftw failed\n");
                exit(1);
        } else if (find == 0) {
                printf("Nerasta nei vieno tinkamo failo\n");
                exit(1);
        }

        return 0;
}
