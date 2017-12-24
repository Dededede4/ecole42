#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define aaaaa
#define bbbbb
#define CS(ignore) int main(){ char *str = "#include <stdio.h>%c#include <fcntl.h>%c#include <unistd.h>%c#define aaaaa%c#define bbbbb%c#define CS(ignore) int main(){ char *str = %c%s%c; int fd=open(%cGrace_kid.c%c,O_WRONLY|O_CREAT|O_TRUNC,0644); dprintf(fd, str, 10, 10, 10, 10, 10, 34, str, 34, 34, 34, 10, 10, 10); close(fd); }%c%c/* Mr rebot lvl 2  */%cCS(0)"; int fd=open("Grace_kid.c",O_WRONLY|O_CREAT|O_TRUNC,0644); dprintf(fd, str, 10, 10, 10, 10, 10, 34, str, 34, 34, 34, 10, 10, 10); close(fd); }

/* Mr rebot lvl 2  */
CS(0)