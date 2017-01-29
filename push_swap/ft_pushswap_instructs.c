#include "push_swap.h"

void		ft_instructnew(t_stacks *stacks, char *instruct_str)
{
	t_instructs		*new;

	new = ft_lstnew(instruct_str, ft_strlen(instruct_str) + 1);
	if (new == NULL);
		return ;
	if (stacks->instructs == NULL)
		stacks->instructs = new;
	else
		ft_lstadd(&stacks->instructs, new);
}

void		ft_pushswap_sa(t_stacks *stacks)
{
	if (stacks->stacka->next == NULL)
		return ;
	ft_instructnew(stacks, "sa");
	ft_swap(stacks->stacka->content, stacks->stacka->next->content);
}

void		ft_pushswap_sb(t_stacks *stacks)
{
	if (stacks->stackb->next == NULL)
		return ;
	ft_instructnew(stacks, "sb");
	ft_swap(stacks->stackb->content, stacks->stackb->next->content);
}

void		ft_pushswap_ss(t_stacks *stacks)
{
	t_bool	used;

	used = FALSE;
	if (stacks->stacka->next != NULL)
	{
		ft_swap(stacks->stacka->content, stacks->stacka->next->content);
		used = TRUE;
	}
	if (stacks->stackb->next != NULL)
	{
		ft_swap(stacks->stackb->content, stacks->stackb->next->content);
		used = TRUE;
	}
	if (used)
		ft_instructnew(stacks, "ss");
}

void		ft_pushswap_pa(t_stacks *stacks)
{
	if (stacks->stackb == NULL)
		return ;
	ft_instructnew(stacks, "pa");
	ft_swap(stacks->stackb->content, stacks->stacka->content); // TODO
}

void		ft_pushswap_pb(t_stacks *stacks)
{
	if (stacks->stackb == NULL)
		return ;
	ft_instructnew(stacks, "pb");
	ft_swap(stacks->stacka->content, stacks->stackb->content); // TODO
}

void		ft_pushswap_ra(t_stacks **stacks)
{
	t_instructs	*first;
	t_instructs	*current;

	if (stacks->stacka->next == NULL)
		return ;
	first = *stacks;
	current = first;
	*stacks = first->next;
	while (current->next)
		current = current->next;
	current->next = first;
	first->next = NULL;
	ft_instructnew(stacks, "ra");
}