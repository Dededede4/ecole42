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

int 		ft_pushswap_quicksort_findlast(t_vals *fixeds, t_vals *lst)
{
	t_vals	*before_last;

	before_last = NULL;
	while (lst)
	{
		if (ft_pushswap_quicksort_isfixed(fixeds, (*((int*)lst->content))))
			return *((int*)before_last->content);
		before_last = lst;
		lst = lst->next;
	}
	return *((int*)before_last->content);
}




int 		ft_pushswap_quicksort_findmin(t_vals *lst)
{
	int min;

	min = (*((int*)lst->content));
	while (lst)
	{
		if (min > (*((int*)lst->content)))
			min = (*((int*)lst->content));
		lst = lst->next;
	}
	return (min);
}

int 		ft_pushswap_quicksort_findmax(t_vals *lst)
{
	int max;

	max = (*((int*)lst->content));
	while (lst)
	{
		if (max < (*((int*)lst->content)))
			max = (*((int*)lst->content));
		lst = lst->next;
	}
	return (max);
}


int 		ft_pushswap_quicksort_mediane(t_vals *fixeds, t_vals *lst)
{
	int 	middle;
	int 	i;
	int 	len;
	t_vals 	*sorted;
	t_vals  *first;
	t_vals  *cpy;

	len = 0;
	i = 0;
	first = lst;
	while (lst)
	{
		if (ft_pushswap_quicksort_isfixed(fixeds, (*((int*)lst->content))))
			break;
		len++;
		lst = lst->next;
	}
	cpy = ft_lstcpy_max(first, len);
	sorted = ft_lstsort(cpy);
	middle = len / 2;
	while (middle && sorted->next && !ft_pushswap_quicksort_isfixed(fixeds, (*((int*)sorted->content))))
	{
		if (i == middle )
			return *((int*)sorted->content);
		i++;
		sorted = sorted->next;
	}
	return  (*((int*)first->content));
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

t_bool			ft_pushswap_quicksort_isallfixed(t_vals **fixeds, t_vals *lst)
{
	while (lst)
	{
		if (!ft_pushswap_quicksort_isfixed(*fixeds, (*((int*)lst->content))))
		{
			return (FALSE);
		}
		lst = lst->next;
	}
	return (TRUE);
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

void 		ft_pushswap_quicksort_a2b_push(t_stacks *stacks, int nbr)
{
	int 	len;
	int 	pos;
	int 	moves;
	int 	sv_moves;
	t_vals	*lst;

	//ft_printf("Move %i \n", nbr);
	pos = 0;
	lst = stacks->stacka;
	len = ft_lstlen(lst);
	while (lst && *((int*)lst->content) != nbr)
	{
		pos++;
		lst = lst->next;
	}
	moves = (pos > (len / 2)) ? pos - len : pos;
	sv_moves = moves;
	while (moves != 0)
	{
		if (moves > 0)
			ft_pushswap_instruct(INSTRUCT_RA, stacks);
		else
			ft_pushswap_instruct(INSTRUCT_RRA, stacks);
		moves += (moves > 0) ? -1 : 1;
	}
	ft_pushswap_instruct(INSTRUCT_PB, stacks);
	/*if (stacks->stackb->next && *((int*)stacks->stackb->content) < *((int*)stacks->stackb->next->content))
		ft_pushswap_instruct(INSTRUCT_SB, stacks);*/
	// pas besoin de faire ça si y'a un FIXED (mais comme c'est extrèmement probable…)
	/*moves = sv_moves;
	if (moves == 0)
		return ;
	moves += (moves > 0) ? 0 : 1;
	while (moves != 0)
	{
		if (moves < 0)
			ft_pushswap_instruct(INSTRUCT_RA, stacks);
		else
			ft_pushswap_instruct(INSTRUCT_RRA, stacks);
		moves += (moves > 0) ? -1 : 1;
	}*/
}

void 		ft_pushswap_quicksort_a2b(t_stacks *stacks, t_vals **f_nbrs)
{
	int 	pivot;
	t_vals	*current;
	t_vals	*first;
	t_vals	*current_fixed;
	int 	last;
	int 	moves;

	while (stacks->stacka)
	{
		/*last = stacks->stacka;
		while (last->next)
			last = last->next;*/
		/*while (1)
		{
			first = stacks->stacka;
			last = stacks->stacka;
			while (last->next)
				last = last->next;
			current = first;
			max = *((int*)current->content);
			while (current->next && !ft_pushswap_quicksort_isfixed(*f_nbrs, *((int*)current->content)))
			{
				if (max < *((int*)current->content))
					max = *((int*)current->content);
				current = current->next;
			}
			
			if (*((int*)last->content) < max)
				ft_pushswap_instruct(INSTRUCT_RRA, stacks);
			else
				break;
		}*/

		/*if (ft_pushswap_quicksort_isallfixed(f_nbrs, stacks->stacka))
			return ;*/

		while (stacks->stacka)
		{
			ft_printf("a...\n");
			last = ft_pushswap_quicksort_findmin(stacks->stacka);
			ft_printf("olala\n");
			if (ft_pushswap_quicksort_isfixed(*f_nbrs, last))
			{
				ft_printf("b...\n");
				ft_pushswap_quicksort_a2b_push(stacks, last);
				ft_printf("c...\n");
			}
			else
				break;
		}
		ft_printf("sortie.\n");
			

		if (stacks->stacka == NULL)
			return ;
		first = stacks->stacka;
		pivot = ft_pushswap_quicksort_mediane(*f_nbrs, first);
		ft_printf("\n\npivot : %d, first: %d\n", pivot, *((int*)first->content));
		ft_printf("Stacka : \n");
		ft_printlst(stacks->stacka);
		ft_printf("\nStackb : \n");
		ft_printlst(stacks->stackb);
		ft_printf("\n Nombres fixes :\n");
		ft_printlst(*f_nbrs);
		ft_printf("\n\n");
		current = first;
		current_fixed = ft_lstcpy(current);
		//ft_printf("start\n");
		while (current_fixed)
		{
			if (*((int*)current_fixed->content) < pivot)
				ft_pushswap_quicksort_a2b_push(stacks, *((int*)current_fixed->content));
			current_fixed = current_fixed->next;
			//ft_printlst(stacks->stackb);
			//ft_printf("\n");
		}
		ft_pushswap_quicksort_setfixed(f_nbrs, pivot);
		ft_pushswap_quicksort_a2b_push(stacks, pivot);

		current = first;
		moves = 0;
		/*ft_printf("segfault ?\n");
		while (stacks->stacka && stacks->stackb->next && last && current)
		{
			ft_printf("i\n");
			if (*((int*)current->content) ==  *((int*)last->content))
				moves++;
			else
				if (moves > 0)
					moves++;
			current = current->next;
		}
		if (moves > 0)
			moves--;
		ft_printf("moves : %i.", moves);
		while (moves--)
			ft_pushswap_instruct(INSTRUCT_RRA, stacks);*/

	}
	ft_pushswap_quicksort_fixalones(f_nbrs, stacks->stacka);
}



void 		ft_pushswap_quicksort_b2a_push(t_stacks *stacks, int nbr)
{
	int 	len;
	int 	pos;
	int 	moves;
	int 	sv_moves;
	t_vals	*lst;

	//ft_printf("Move %i \n", nbr);
	pos = 0;
	lst = stacks->stackb;
	len = ft_lstlen(lst);
	while (lst && *((int*)lst->content) != nbr)
	{
		pos++;
		lst = lst->next;
	}
	moves = (pos > (len / 2)) ? pos - len : pos;
	sv_moves = moves;
	while (moves != 0)
	{
		if (moves > 0)
			ft_pushswap_instruct(INSTRUCT_RB, stacks);
		else
			ft_pushswap_instruct(INSTRUCT_RRB, stacks);
		moves += (moves > 0) ? -1 : 1;
	}
	ft_pushswap_instruct(INSTRUCT_PA, stacks);
	/*if (stacks->stacka->next && *((int*)stacks->stacka->content) > *((int*)stacks->stacka->next->content))
		ft_pushswap_instruct(INSTRUCT_SA, stacks);*/
	// pas besoin de faire ça si y'a un FIXED (mais comme c'est extrèmement probable…)
	/*moves = sv_moves;
	if (moves == 0)
		return ;
	moves += (moves > 0) ? 0 : 1;
	while (moves != 0)
	{
		if (moves < 0)
			ft_pushswap_instruct(INSTRUCT_RB, stacks);
		else
			ft_pushswap_instruct(INSTRUCT_RRB, stacks);
		moves += (moves > 0) ? -1 : 1;
	}*/
}

void 		ft_pushswap_quicksort_b2a(t_stacks *stacks, t_vals **f_nbrs)
{
	int 	pivot;
	t_vals	*current;
	t_vals	*first;
	t_vals	*current_fixed;
	int 	last;
	//int 	moves;

	while (stacks->stackb)
	{
		while (stacks->stackb)
		{
			last = ft_pushswap_quicksort_findmax(stacks->stackb);
			if (ft_pushswap_quicksort_isfixed(*f_nbrs, last))
				ft_pushswap_quicksort_b2a_push(stacks, last);
			else
				break;
		}

		/*while (1)
		{
			first = stacks->stackb;
			last = stacks->stackb;
			while (last->next)
				last = last->next;
			current = first;
			min = *((int*)current->content);
			while (current->next && !ft_pushswap_quicksort_isfixed(*f_nbrs, *((int*)current->content)))
			{
				if (min > *((int*)current->content))
					min = *((int*)current->content);
				current = current->next;
			}
			
			if (*((int*)last->content) > min)
				ft_pushswap_instruct(INSTRUCT_RRB, stacks);
			else
				break;
		}*/

/*
		while (stacks->stackb && ft_pushswap_quicksort_isfixed(*f_nbrs, *((int*)stacks->stackb->content)))
			ft_pushswap_instruct(INSTRUCT_PA, stacks);*/
		if (stacks->stackb == NULL)
			return ;
		first = stacks->stackb;
		pivot = ft_pushswap_quicksort_mediane(*f_nbrs, first);
		ft_printf("\n\npivot : %d, first: %d\n", pivot, *((int*)first->content));
		ft_printf("Stacka : \n");
		ft_printlst(stacks->stacka);
		ft_printf("\nStackb : \n");
		ft_printlst(stacks->stackb);
		ft_printf("\n Nombres fixes :\n");
		ft_printlst(*f_nbrs);
		ft_printf("\n\n");
		current = first;
		current_fixed = ft_lstcpy(current);
		//ft_printf("start\n");
		while (current_fixed)
		{
			if (*((int*)current_fixed->content) > pivot)
				ft_pushswap_quicksort_b2a_push(stacks, *((int*)current_fixed->content));
			current_fixed = current_fixed->next;
			//ft_printlst(stacks->stackb);
			//ft_printf("\n");
		}
		ft_pushswap_quicksort_setfixed(f_nbrs, pivot);
		ft_pushswap_quicksort_b2a_push(stacks, pivot);

		/*current = stacks->stackb;
		moves = 0;
		while (current)
		{
			if (*((int*)current->content) ==  *((int*)last->content))
				moves++;
			else
				if (moves > 0)
					moves++;
			current = current->next;
		}
		if (moves > 0)
			moves--;
		ft_printf("\nMoves b2a : %i\n", moves);
		while (moves--)
			ft_pushswap_instruct(INSTRUCT_RRB, stacks);*/

	}
	ft_pushswap_quicksort_fixalones(f_nbrs, stacks->stacka);
}

t_stacks		*ft_pushswap_quicksort(t_vals *vals)
{
	t_stacks *stacks;
	t_vals	*f_nbrs;
	size_t len;
	//int i = 0;

	f_nbrs = NULL;
	stacks = malloc(sizeof(t_stacks));
	stacks->stacka = ft_lstcpy(vals);
	stacks->stackb = NULL;
	stacks->instructs = NULL;
	len = ft_lstlen(stacks->stacka);
	while (!ft_pushswap_quicksort_issorted(stacks->stacka) && len != ft_lstlen(f_nbrs))
	{
		ft_pushswap_quicksort_a2b(stacks, &f_nbrs);
		/*ft_printf("Stacka : \n");
		ft_printlst(stacks->stacka);
		ft_printf("\nStackb : \n");
		ft_printlst(stacks->stackb);
		ft_printf("\n Nombres fixes :\n");
		ft_printlst(f_nbrs);
		ft_printf("\n\n");*/
		ft_pushswap_quicksort_b2a(stacks, &f_nbrs);
		/*ft_printf("\n 2 Stacka : \n");
		ft_printlst(stacks->stacka);
		ft_printf("\n 2 Stackb : \n");
		ft_printlst(stacks->stackb);
		ft_printf("\n 2 Nombres fixes :\n");
		ft_printlst(f_nbrs);
		ft_printf("\n\n");
		ft_printf("\n\n");*/
		/*if (i == 5)
			exit(0);
		i++;*/
	}
	ft_printf("\n");
	ft_printlst(stacks->stacka);

	if (ft_pushswap_quicksort_issorted(stacks->stacka))
		ft_printf("\n\n\n trie :) \n\n\n");
	else
		ft_printf("\n\n\n PAS TRIE DU TOUT :( :( \n\n\n");
	//ft_printlst_str(stacks->instructs);
	// //ft_printf("A T ON GAGNE ? =>%d<=\n\n\n", ft_lstlen(stacks->instructs));
	return stacks;
}