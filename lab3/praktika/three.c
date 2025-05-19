#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#define SIZE 1048576

int ig_open_rdonly(const char *name, int flags){
   int dskr;
   dskr = open( name, O_RDONLY );
   if( dskr == -1 ){
      perror( name );
      abort();
   }
   printf( "Failas \"%s\" atidarytas, jo fd = %d\n", name, dskr );
   return dskr;
}

int ig_open(const char *name, int flags, mode_t mode){
   int dskr;
   dskr = open( name, flags, mode );
   if( dskr == -1 ){
      perror( name );
      abort();
   }
   printf( "Failas \"%s\" atidarytas, jo fd = %d\n", name, dskr );
   return dskr;
}

int main(int argc, char *argv[]){
	printf( "(C) 2022 , %s\n", __FILE__ );
	
	// 1.
	if (argc != 4) {
	   fprintf(stderr, "Turite nurodyti 3 argumentus (failo_vardas (failas), N (skaičius), M (skaičius))\n");
	   exit(211);
	}

	struct stat sb;
	if (stat(argv[1], &sb) == -1) {
	   perror("stat");
	   abort();
	}
	
	if ((sb.st_mode & S_IFMT) != S_IFREG){
		printf("Pirmu argumentu nurodytas ne failas\n");
		abort();
	}
	
	int N = atoi(argv[2]);
	int M = atoi(argv[3]);
	
	// 2. 
	int fd;
	fd = ig_open_rdonly( argv[1], O_RDONLY);
	
	// 3.
	lseek(fd, (sb.st_size / sizeof(char) - N), SEEK_SET);
	char buf[SIZE];
	int r = read(fd, buf, M);
	if (r == -1){
		perror("read");
		abort();
	}

	// 4.
	if (r > 0) {
		int fd2 = ig_open( "data.bin", O_WRONLY | O_CREAT | O_TRUNC, 0777 );
		chmod("data.bin", 0777);
		if (write(fd2, buf, r) == -1) {
			perror("write");
			abort();
		}
		printf("Duomenys buvo įrašyti į \"data.bin\"\n");
		
		// 6.
		printf("Pirmas nukopijuotas baitas - %c\n", buf[0]);
		printf("Paskutinis nukopijuotas baitas - %c\n", buf[r-1]);
	} 
	// 5. 
	else {
		printf("Faile \"%s\" nėra ką skaityti\n", argv[1]);
	}
	
	return 0;
}
