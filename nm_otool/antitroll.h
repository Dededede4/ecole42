#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct					s_command
{
	t_list						*bss_numbers;
	t_list						*const_numbers;
	t_list						*data_numbers;
	t_list						*text_numbers;

}								t_command;

t_command command;

typedef	struct 					s_line
{
	uint64_t		left;
	char			middle;
	char			*right;
	t_bool			is_64;
	t_bool			is_32;
	struct s_line	*next;
}								t_line;

void ifexit(t_bool cond, int nbr);
t_line	*get_line_trololo(
	struct symtab_command *sym, char *ptr, off_t size);
t_line	*get_line_trololo_32(
	struct symtab_command *sym, char *ptr, off_t size);
void handle_64_trololo_segment(void *ptr, off_t size, void *lc, int *ycount);
void handle_64_trololo(char * ptr, off_t size);
void handle_32_trololo_segment(void *ptr, off_t size, void *lc, int *ycount);
void handle_32_trololo(char * ptr, off_t size);
void handle_fat_trololo(char *ptr, off_t size);
void antitroll(char *ptr, off_t size);
unsigned int ft_nxswaplong(unsigned int nbr);
unsigned int nsl(unsigned int nbr);