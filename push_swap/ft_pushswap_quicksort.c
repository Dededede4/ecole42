#include "push_swap.h"

t_bool 			ft_pushswap_quicksort_issorted(t_vals *lst)
{
	int p;

	p = *((int*)lst->content);
	while(lst)
	{
		if (p > *((int*)lst->content))
			return (FALSE);
		p = *((int*)lst->content);
		lst = lst->next;
	}
	return (TRUE);
}

t_bool 			ft_pushswap_quicksort_isfixed(t_vals *fixeds, int nbr)
{
	while(fixeds)
	{
		if (*((int*)fixeds->content) == nbr)
			return (TRUE);
		fixeds = fixeds->next;
	}
	return (FALSE);
}

t_vals			*ft_pushswap_quicksort_findfirst(t_vals *fixeds, t_vals *lst)
{
	while (lst)
	{
		if (!(ft_pushswap_quicksort_isfixed(fixeds, (*((int*)lst->content)))))
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}

t_vals			*ft_pushswap_quicksort_findlast(t_vals *fixeds, t_vals *lst)
{
	t_vals	*before_last;

	before_last = NULL;
	while (lst)
	{
		if (ft_pushswap_quicksort_isfixed(fixeds, (*((int*)lst->content))))
			return (before_last);
		before_last = lst;
		lst = lst->next;
	}
	return (before_last);
}

void			ft_pushswap_quicksort_setfixed(t_vals **fixeds, int nbr)
{
	if (*fixeds == NULL)
		*fixeds = ft_lstnew(&nbr, sizeof(int));
	else
	{
		if (!ft_pushswap_quicksort_isfixed(*fixeds, nbr))
			ft_lstadd(fixeds, ft_lstnew(&nbr, sizeof(int)));
	}
}

void			ft_pushswap_quicksort_fixalones(t_vals **fixeds, t_vals *lst)
{
	int length;
	int prec;

	length = -1;
	while (lst)
	{
		if (ft_pushswap_quicksort_isfixed(*fixeds, *((int*)lst->content)))
		{
			if (length == 1)
			{
				ft_pushswap_quicksort_setfixed(fixeds, prec);
			}
			length = 0;
		}
		else
		{
			length++;
		}
		prec = *((int*)lst->content);
		lst = lst->next;
	}
}

void 		ft_pushswap_quicksort_a2b(t_stacks *stacks, t_vals **f_nbrs)
{
	int 	pivot;
	t_vals	*current;
	t_vals	*first;
	t_vals	*next;
	int 	rollback;

	rollback = 0;
	while (stacks->stacka)
	{
		while (stacks->stacka && ft_pushswap_quicksort_isfixed(*f_nbrs, *((int*)stacks->stacka->content)))
			ft_pushswap_instruct(INSTRUCT_PB, stacks);
		if (stacks->stacka == NULL)
			return ;
		first = stacks->stacka;
		current = ft_pushswap_quicksort_findlast(*f_nbrs, first);
		pivot = *((int*)current->content);
		////ft_printf("\n\npivot : %d, first: %d\n\n", pivot, *((int*)first->content));
		current = first;
		////ft_printf("start\n");
		while (current && !ft_pushswap_quicksort_isfixed(*f_nbrs, (*((int*)current->content))))
		{
			next = current->next;
			////ft_printf("\n%d <= %d\n", *((int*)current->content), pivot);
			if (*((int*)current->content) < pivot)
				ft_pushswap_instruct(INSTRUCT_PB, stacks);
			else if (*((int*)current->content) > pivot)
			{
				ft_pushswap_instruct(INSTRUCT_RA, stacks);
				rollback++;
			}
			else
			{
				ft_pushswap_quicksort_setfixed(f_nbrs, pivot);
				ft_pushswap_instruct(INSTRUCT_PB, stacks);
				while (rollback--)
				{
					ft_pushswap_instruct(INSTRUCT_RRA, stacks);
				}
				rollback = 0;
				break;
			}
			current = next;
			////ft_printlst(stacks->stacka);
			////ft_printf("\n");
		}
	}

	ft_pushswap_quicksort_fixalones(f_nbrs, stacks->stackb);
}

void 		ft_pushswap_quicksort_b2a(t_stacks *stacks, t_vals **f_nbrs)
{
	int 	pivot;
	t_vals	*current;
	t_vals	*first;
	t_vals	*next;
	int 	rollback;

	rollback = 0;
	while (stacks->stackb)
	{
		while (stacks->stackb && ft_pushswap_quicksort_isfixed(*f_nbrs, *((int*)stacks->stackb->content)))
			ft_pushswap_instruct(INSTRUCT_PA, stacks);
		if (stacks->stackb == NULL)
			return ;
		first = stacks->stackb;
		current = ft_pushswap_quicksort_findlast(*f_nbrs, first);
		pivot = *((int*)current->content);
		//ft_printf("\n\npivot : %d, first: %d\n\n", pivot, *((int*)first->content));
		current = first;
		//ft_printf("start\n");
		while (current && !ft_pushswap_quicksort_isfixed(*f_nbrs, (*((int*)current->content))))
		{
			next = current->next;
			//ft_printf("\n%d >= %d\n", *((int*)current->content), pivot);
			if (*((int*)current->content) > pivot)
				ft_pushswap_instruct(INSTRUCT_PA, stacks);
			else if (*((int*)current->content) < pivot)
			{
				ft_pushswap_instruct(INSTRUCT_RB, stacks);
				rollback++;
			}
			else
			{
				ft_pushswap_quicksort_setfixed(f_nbrs, pivot);
				ft_pushswap_instruct(INSTRUCT_PA, stacks);
				while (rollback--)
				{
					ft_pushswap_instruct(INSTRUCT_RRB, stacks);
				}
				rollback = 0;
				break;
			}
			current = next;
			//ft_printlst(stacks->stackb);
			//ft_printf("\n");
		}
	}
	ft_pushswap_quicksort_fixalones(f_nbrs, stacks->stacka);
}

t_stacks		*ft_pushswap_quicksort(t_vals *vals)
{
	t_stacks *stacks;
	t_vals	*f_nbrs;
	//int i = 0;

	f_nbrs = NULL;
	stacks = malloc(sizeof(t_stacks));
	stacks->stacka = ft_lstcpy(vals);
	stacks->stackb = NULL;
	stacks->instructs = NULL;
	while (!ft_pushswap_quicksort_issorted(stacks->stacka))
	{
		ft_pushswap_quicksort_a2b(stacks, &f_nbrs);
		//ft_printf("Stacka : \n");
		//ft_printlst(stacks->stacka);
		//ft_printf("\nStackb : \n");
		//ft_printlst(stacks->stackb);
		//ft_printf("\n Nombres fixes :\n");
		//ft_printlst(f_nbrs);
		//ft_printf("\n\n");
		ft_pushswap_quicksort_b2a(stacks, &f_nbrs);
		//ft_printf("\n 2 Stacka : \n");
		//ft_printlst(stacks->stacka);
		//ft_printf("\n 2 Stackb : \n");
		//ft_printlst(stacks->stackb);
		//ft_printf("\n 2 Nombres fixes :\n");
		//ft_printlst(f_nbrs);
		//ft_printf("\n\n");
		//ft_printf("\n\n");
		/*if (i == 5)
			exit(0);
		i++;*/
	}
	// //ft_printf("A T ON GAGNE ? =>%d<=\n\n\n", ft_lstlen(stacks->instructs));
	return stacks;
}