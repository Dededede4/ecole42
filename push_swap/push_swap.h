#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

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
void	ft_pushswap_sa(t_stacks *stacks);


t_instructs		*ft_pushswap_stupidsort(t_vals *vals);

int		*ft_intdup(int nbr);
t_list	*ft_lstcpy(t_list *src);
#endif