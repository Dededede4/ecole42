#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>

#include "libft/libft.h"

int     voir_touche();
void t_enable_insert_mode();
void t_delete_last_char();

void see()
{
	char ch;
	while (1) {
		if (read(0, &ch, 1) > 0) 
			ft_printf(" %b\n", ch);
	}
}

void simpleput()
{
	char ch;
	while (1) {
		if (read(0, &ch, 1) > 0)
		{
			if (ch == 127)
				t_delete_last_char();
			else
				ft_putchar(ch);
		}
	}
}
int              main()
{
	char           *name_term;
	struct termios term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	// remplis la structure termios des possibilités du terminal.
	if (tcgetattr(0, &term) == -1)
		return (-1);

	term.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
	term.c_lflag &= ~(ECHO); // les touches tapées ne s'inscriront plus dans le terminal
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	// On applique les changements :
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	t_enable_insert_mode();
	 simpleput();
}

void t_enable_insert_mode()
{
	char *str = tgetstr("im", NULL);

	tputs(str, ft_strlen(str), ft_putchar);
	//ft_strdel(&str);	 TODO FREE
}

void t_disable_insert_mode()
{
	char *str = tgetstr("ei", NULL);

        tputs(str, ft_strlen(str), ft_putchar);
}

void t_move_left()
{
	char *str = tgetstr("le", NULL);

	tputs(str, ft_strlen(str), ft_putchar);
}

void t_delete_last_char()
{
        char *str = tgetstr("dc", NULL);

	//t_disable_insert_mode();
	t_move_left();
        tputs(str, ft_strlen(str), ft_putchar);
	//t_enable_insert_mode();
        //ft_strdel(&str);       TODO FREE
}

void	tc_putstr()
{
	char *res;

#ifdef Unix
	/* Here we assume that an explicit term_buffer
	   was provided to tgetent.  */
	char *buffer
		= (char *) malloc (strlen (term_buffer));
#define BUFFADDR &buffer
#else
#define BUFFADDR 0
#endif

	res = tgetstr("cm", BUFFADDR);
	/*
	 ** On utilise la fonction tgoto, qui va retourner une série d'instructions (sous forme de chaine de caractère)
	 ** afin de déplacer le curseur jusqu'à l'endroit voulu.
	 */
	tputs(tgoto(res, 0, 0), 1, putchar);
	printf("coucou mon coco bg");
}


int ft_putchar_unicode(int c)
{
	ft_printf("%lc", c);
	return 0;
}


void t_putstr(char *str)
{
	tputs(str, ft_strlen(str), ft_putchar_unicode);
}

int     voir_touche()
{
	int     buffer;
	int	c;

	//t_putstr("$ > ");
	while (1)
	{
		read(0, &buffer, 4);
		/*if (buffer[0] == 27)
		  printf("C'est une fleche !\n");
		  else if (buffer[0] == 4)
		  {
		  printf("Ctlr+d, on quitte ! (mais sinon on fait une recherche)\n");
		  return (0);
		  }
		  else
		  {*/
		ft_printf("%lc\n", buffer);
		/*}*/
	}
	return (0);
}

