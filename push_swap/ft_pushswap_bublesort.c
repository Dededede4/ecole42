#include "push_swap.h"

size_t 		ft_lstlen(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}


void		ft_lstmove(t_list **lst, size_t len)
{
	size_t	i;
	t_list	*first;
	t_list	*current;
	t_list	*before_current;

	if (len == 0)
		return;
	i = 0;
	first = *lst;
	current = first;
	before_current = NULL;
	while (current)
	{
		if (i == len)
		{
			*lst = current;
			if (before_current)
				before_current->next = NULL;
		}
		i++;
		before_current = current;
		current = current->next;
	}
	before_current->next = first;
}
int 		ft_pushswap_bublesort_findsup(t_vals *vals, int start)
{
	t_vals	*ovals;
	//t_vals	*ovals_first;
	int 	i;
	int 	p_val;
	size_t	len;
	int 	tmp;

	i = 0;
	ovals = ft_lstcpy(vals);
	len = ft_lstlen(vals);
	//ovals_first = ovals;
	ft_lstmove(&ovals, (size_t)start);


	/*ft_printf("Reconstitued ");
	ft_printlst(ovals);
	ft_printf("\n");*/

	p_val = *((int*)ovals->content);
	while (ovals)
	{
		//ft_printf("%d > %d\n", p_val, *((int*)ovals->content));
		if (p_val > *((int*)ovals->content))
		{
			// return (((pos <= (length / 2) && pos >= 0) || (pos >= (length / 2) && pos < 0) ? pos : 0 - (length - pos)));
			//ft_printf("i:%i start:%i\n", i, start);
			tmp = (((i) + start) % (int)len);
			tmp = ((tmp <= ((int)len / 2) ? tmp - 1 : ((0 - (int)len) + tmp)));
			return (tmp);
		}
		p_val = *((int*)ovals->content);
		i++;
		ovals = ovals->next;
	}
	return (-42);
}



t_instructs		*ft_pushswap_bublesort(t_vals *vals)
{
	t_stacks *stacks;
	int 		moves;
	int 		savemoves;
	int 		index;
	int 		len;
	//int 		debug;


	stacks = malloc(sizeof(t_stacks));
	stacks->stacka = ft_lstcpy(vals);
	len = (int)ft_lstlen(vals);

	/*ft_printlst(stacks->stacka);
	ft_printf("\n\n");*/
	index = 0;
	//debug = 0;

	while ((moves = ft_pushswap_bublesort_findsup(stacks->stacka, index)) != -42)
	{
		/*if (moves < 0)
			moves++;
		if (moves > 0)
			moves--;*/
		//moves--;
		savemoves = moves;
		
		//ft_printf("Moves ==>%d<==\n", moves);
		while (moves != 0)
		{
			
			if (moves > 0)
				ft_pushswap_instruct(INSTRUCT_RRA, stacks);
			else if (moves < 0)
				ft_pushswap_instruct(INSTRUCT_RA, stacks);
			moves += (moves > 0) ? -1 : 1;

			//ft_printlst(stacks->stacka);
			//ft_printf("\n");
		}
		ft_pushswap_instruct(INSTRUCT_SA, stacks);
		//ft_printlst(stacks->stacka);
		
		if (savemoves < 0)
		{
			index = index - savemoves;
			index = index % len;
		}
		else if (savemoves > 0)
		{
			index = (index + (len - savemoves)) % len;
		}
		//ft_printf("\nIndex : %d\n\n", index);
		/*debug++;
		if (debug == 100)
		{
			ft_printf("stop");
			exit(0);
		}*/
	}
	while (index--)
	{
		ft_pushswap_instruct(INSTRUCT_RRA, stacks);
		vals = vals->next;
	}
	/*ft_printf("Final :\n");
	ft_printlst(stacks->stacka);
	ft_printf("\n");*/
	//ft_printlst_str(stacks->instructs);
	return stacks->instructs;
}

