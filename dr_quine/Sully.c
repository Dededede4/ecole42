#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int i = 5;
	char filename[256];
	char command_compile[256];
	char command_exec[256];
	sprintf(filename, "Sully_%d.c", i);
	sprintf(command_compile, "cc Sully_%d.c -o Sully_%d", i, i);
	sprintf(command_exec, "./Sully_%d", i);
	int fd = open(filename,O_WRONLY|O_CREAT|O_TRUNC,0644);
	i--;
	char *str = "#include <stdio.h>%c#include <fcntl.h>%c#include <unistd.h>%c#include <stdlib.h>%cint main()%c{%c	int i = %d;%c	char filename[256];%c	char command_compile[256];%c	char command_exec[256];%c	sprintf(filename, %cSully_%%d.c%c, i);%c	sprintf(command_compile, %ccc Sully_%%d.c -o Sully_%%d%c, i, i);%c	sprintf(command_exec, %c./Sully_%%d%c, i);%c	int fd = open(filename,O_WRONLY|O_CREAT|O_TRUNC,0644);%c	i--;%c	char *str = %c%s%c;%c	dprintf(fd, str, 10, 10, 10, 10, 10, 10, i, 10, 10, 10, 10, 34, 34, 10, 34, 34, 10, 34, 34, 10, 10, 10, 34, str, 34, 10, 10, 10, 10, 10, 10, 10, 10);%c	close(fd);%c	system(command_compile);%c	if (i > 0)%c		system(command_exec);%c	return (0);%c}";
	dprintf(fd, str, 10, 10, 10, 10, 10, 10, i, 10, 10, 10, 10, 34, 34, 10, 34, 34, 10, 34, 34, 10, 10, 10, 34, str, 34, 10, 10, 10, 10, 10, 10, 10, 10);
	close(fd);
	system(command_compile);
	if (i > 0)
		system(command_exec);
	return (0);
}