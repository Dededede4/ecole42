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
# define INSTRUCT_RR 10
# define INSTRUCT_RRR 11

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


t_stacks		*ft_pushswap_selectsort(t_vals *vals);
t_stacks		*ft_pushswap_quicksort(t_vals *vals);

void		ft_pushswap_instruct(char instruct, t_stacks *stacks);

int		*ft_intdup(int nbr);
t_list	*ft_lstcpy(t_list *src);
size_t 		ft_lstlen(t_list *lst);
t_list		*ft_lstsort(t_list *lst);
t_list	*ft_lstcpy_max(t_list *src, size_t max);
t_list		*ft_lstsort_rev(t_list *lst);
void 	ft_lstadd_end(t_list **lst, t_list *new);
t_bool 			ft_intlst_issorted(t_vals *lst);

t_bool			ft_pushswap_quicksort_isfixed(t_vals *fixeds, int nbr);
t_vals		*ft_pushswap_quicksort_findfirst(t_vals *fixeds, t_vals *lst);
int		ft_pushswap_quicksort_findlast(t_vals *fixeds, t_vals *lst);
int		ft_pushswap_quicksort_findmin(t_vals *lst);
int		ft_pushswap_quicksort_findmax(t_vals *lst);
int 		ft_pushswap_quicksort_mediane(t_vals *fixeds, t_vals *lst);
void			ft_pushswap_quicksort_setfixed(t_vals **fixeds, int nbr);
t_bool			ft_pushswap_quicksort_isallfixed(t_vals **fixeds, t_vals *lst);
void			ft_pushswap_quicksort_fixalones(t_vals **fixeds, t_vals *lst);
#endif