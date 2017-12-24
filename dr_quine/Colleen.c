#include <stdio.h>

/* Mon correcteur est le plus beau */

void display()
{
	char *str = "#include <stdio.h>%c%c/* Mon correcteur est le plus beau */%c%cvoid display()%c{%c	char *str = %c%s%c;%c	printf(str, 10, 10, 10, 10, 10, 10, 34, str, 34, 10, 10, 10, 10, 10, 10, 10, 10, 10);%c}%c %cint main()%c{%c	/* Mr rebot lvl 1 */%c	display();%c}%c";
	printf(str, 10, 10, 10, 10, 10, 10, 34, str, 34, 10, 10, 10, 10, 10, 10, 10, 10, 10);
}
 
int main()
{
	/* Mr rebot lvl 1 */
	display();
}
