#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

# define INSTRUCT_SA 1
# define INSTRUCT_SB 2
# define INSTRUCT_SS 3
# define INSTRUCT_PA 4
# define INSTRUCT_PB 5
# define INSTRUCT_RA 6
# define INSTRUCT_RB 7
# define INSTRUCT_RRA 8
# define INSTRUCT_RRB 9

typedef t_list				t_instructs;
typedef t_list				t_vals;

typedef struct          s_stacks
{
        
        t_instructs		*instructs;
        t_vals			*stacka;
        t_vals			*stackb;
}                      	t_stacks;


t_list		*ft_arraytolst(char **str, int size);
void	ft_printlst(t_list *lst);
void	ft_printlst_str(t_list *lst);


t_instructs		*ft_pushswap_selectsort(t_vals *vals);
t_instructs		*ft_pushswap_bublesort(t_vals *vals);
t_instructs		*ft_pushswap_quicksort(t_vals *vals);

void		ft_pushswap_instruct(char instruct, t_stacks *stacks);

int		*ft_intdup(int nbr);
t_list	*ft_lstcpy(t_list *src);
size_t 		ft_lstlen(t_list *lst);
#endif