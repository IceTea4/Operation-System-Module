#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <ftw.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/mman.h>

int reg_open(const char *name)
	{
		int fd = open(name, O_RDONLY);
		if (fd == -1) {
			puts(name);
			puts("Failas nevykdomas");}
		return fd;
	}

int kp_test_close(int fd){
   int rv;
   rv = close( fd );
   if( rv != 0 ) {perror ( "close() failed" );
   abort();}
   return rv;
}

int printFiles(const char *filename, const struct stat *statptr,
    int tflag, struct FTW *pfwt)
	
{
		struct stat buff;
        printf("%s ", filename + pfwt->base);
        printf("Tipas: ");
		if( S_ISBLK(statptr->st_mode)==1) {
		printf("block special file"); }
		if( S_ISSOCK(statptr->st_mode)==1) {
		printf("socket"); }    
		if( S_ISCHR(statptr->st_mode)==1) {
		printf("character special file"); }    
		if( S_ISDIR(statptr->st_mode)==1) { 
		printf("directory"); }
		if( S_ISFIFO(statptr->st_mode)==1) {
		printf("pipe or FIFO special file"); }    
		if( S_ISREG(statptr->st_mode)==1) 
		{
		stat(filename,&buff);
		printf("regular file\n");
		if(((buff.st_mode & S_IXUSR)? "r":NULL) != NULL)
		{
			char buf[4];
		
			int f;
			f = reg_open(filename);
			read(f,buf,4);
			if (buf[0] == 127 && buf[1] == 69 && buf[2] == 76 && buf[3] == 70 )
			{
				printf( "ELF yra pagal turini \n");
		
			} 
			else {
				printf( "ELF nera pagal turini \n");
				kp_test_close(f);
			}
		}
		else
		{
			printf("\n");
			puts(filename);
			puts("Nevykdomas");
		}
		
	}     
		if( S_ISLNK(statptr->st_mode)==1) {
		printf("symbolic link"); }
    
		printf("\n");
	
    return 0;
}
int main(int argc, char * argv[])
{
    int count=0;
    struct stat buff;
    int fd_limit = 20;
    int flags = FTW_DEPTH | FTW_MOUNT | FTW_PHYS; 
    int ret;
	int openF;
	int readK;
    DIR *d = opendir(argv[1]);
    struct dirent *dirfile;
	char *buf;
    buf=(char*) malloc(50);
	printf("Darba atliko \n");
    if (argc != 3)
    {
        puts("Netinkamas argumentu skaicius");
        exit(110);
    }
    stat(argv[1],&buff);
    if (S_ISDIR(buff.st_mode) ==1)
    {
		puts("Pirmas failas direktorija");
		
		openF = open(argv[2], O_RDONLY);

		readK = read(openF,buf , 50);
	
		close(openF);
		if (readK == 0)
		{
			puts("Filas yra tuscias \n");
			exit(111);
		}
			else
		{
			puts("Pratesime darba failas netuscias");
		}
        while ((dirfile = readdir(d)) != NULL)
        {
                count++;
        }
        closedir(d);
        if (count==2)
        {
        puts("Directorija tuscia");
        abort();
        }
        else
        {

			printf("Pirmo failo vardas %s \n", argv[1]);
			printf("Antro failo vardas failo vardas %s \n", argv[2]);	
			ret = nftw(argv[1], printFiles, fd_limit, flags); 
			if( ret == -1 ) 
			{
			abort();
			}
        }
		
	if( ret != 0 ) {
      printf( "Pavyko \n");
	}
  
    }
	else{
		puts("Pirmas argumentas turi buti katalogas");
		abort();
	}
	
	printf("Darba atliko Kristijonas Kavaliauskas IFA02 \n");
	

}
