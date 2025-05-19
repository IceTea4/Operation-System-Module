#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // 1
    if (argc != 4)
    {
        printf("Naudojimas: %s <failo_vardas>, <N>, <M>\n", __FILE__);
        return 205;
    }

    int fd;

    // 2
    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
        printf("Luzo open %s\n", argv[1]);
        abort();
    }

    // 3
    int N = atoi(argv[2]);
    int M = atoi(argv[3]);

    if (lseek(fd, N, SEEK_SET) == -1)
    {
        printf("Luzo seek\n");
        abort();
    }

    char buffer[M];

    if (read(fd, &buffer, M) == -1)
    {
        printf("Luzo read\n");
        abort();
    }

    // 6
    if (strlen(buffer) != sizeof(buffer))
    {
        abort();
    }

    // 4
    int fd2;
    if ((fd2 = open("data.bin", O_CREAT | O_TRUNC | O_WRONLY)) == -1)
    {
        printf("Luzo open data.bin\n");
        abort();
    }

    if (write(fd2, &buffer, M) == -1)
    {
        printf("Luzo write\n");
        abort();
    }

    // 5
    if(chmod("data.bin", S_IRUSR | S_IWUSR | S_IXUSR | S_IROTH | S_IWOTH | S_IXOTH) == -1)
    {
        printf("Luzo chmod\n");
        abort();
    }

    return 0;
}
