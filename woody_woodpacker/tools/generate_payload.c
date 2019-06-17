#include <stdio.h> 
#include <fcntl.h> 
#include <errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
extern int errno; 

/*
 * function to open binary and get its size, doesn't map it yet
 * you have to close fd yourself
 * return file fd or -1 on error, take pointer on int for size
 */
static int	open_file(char const *name, size_t *size)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0) {
		perror("open");
	} else {
		*size = lseek(fd, 0, SEEK_END);
		if ((int)(*size) < 0) {
			perror("lseek");
			close(fd);
			fd = -1;
		}
	}
	return fd;
}

int main() 
{      
    // if file does not have in directory  
    // then file foo.txt is created. 
    int fd = open("virus.bin", O_RDONLY);
    size_t size;
    unsigned char buff[1024];
    int len;
    int i = 0;
    int done;

    open_file("virus.bin", &size);
    done = 0;
   if (fd > 0)
   {
   		printf("unsigned char virus[%zu] = {\n", size);
	   while ((len = read(fd, buff, 16)) > 0)
	   {
	   		while (i < len)
	   		{
	   			printf("0x%02x", buff[i]);
	   			i++;
	   			done++;

	   			if (done < size)
	   				printf(", ");
	   		}

	   		printf("\n");
	   		i = 0;
	   }

	   printf("};\n");

	}

    return 0; 
} 
