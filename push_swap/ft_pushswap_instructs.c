#include "push_swap.h"

void		ft_instructnew(t_stacks *stacks, char *instruct_str)
{
	t_instructs		*new;

	new = ft_lstnew(instruct_str, ft_strlen(instruct_str) + 1);
	if (new == NULL)
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
	t_vals	*tmp;

	if (stacks->stackb == NULL)
		return ;
	ft_instructnew(stacks, "pa");
	tmp = stacks->stackb->next;
	stacks->stackb->next = stacks->stacka;
	stacks->stacka = stacks->stackb;
	stacks->stackb = tmp;
}

void		ft_pushswap_pb(t_stacks *stacks)
{
	t_vals	*tmp;

	if (stacks->stacka == NULL)
		return ;
	ft_instructnew(stacks, "pb");
	tmp = stacks->stacka->next;
	stacks->stacka->next = stacks->stackb;
	stacks->stackb = stacks->stacka;
	stacks->stacka = tmp;
}

void		ft_pushswap_ra(t_stacks *stacks)
{
	t_vals	*first;
	t_vals	*current;

	if (stacks->stacka->next == NULL)
		return ;
	first = stacks->stacka;
	current = first;
	stacks->stacka = first->next;
	while (current->next)
		current = current->next;
	current->next = first;
	first->next = NULL;
	ft_instructnew(stacks, "ra");
}

void		ft_pushswap_rb(t_stacks *stacks)
{
	t_vals	*first;
	t_vals	*current;

	if (stacks->stackb->next == NULL)
		return ;
	first = stacks->stackb;
	current = first;
	stacks->stackb = first->next;
	while (current->next)
		current = current->next;
	current->next = first;
	first->next = NULL;
	ft_instructnew(stacks, "rb");
}

void		ft_pushswap_rra(t_stacks *stacks)
{
	t_vals	*first;
	t_vals	*current;
	t_vals *before_last;

	if (stacks->stacka->next == NULL)
		return ;
	first = stacks->stacka;
	current = first;
	stacks->stacka = first->next;
	while (current->next)
	{
		before_last = current;
		current = current->next;
	}
	before_last->next = NULL;
	current->next = first;
	first = current;
	first->next = NULL;
	ft_instructnew(stacks, "ra");
}

void		ft_pushswap_rrb(t_stacks *stacks)
{
	t_vals	*first;
	t_vals	*current;
	t_vals *before_last;

	if (stacks->stackb->next == NULL)
		return ;
	first = stacks->stackb;
	current = first;
	stacks->stackb = first->next;
	while (current->next)
	{
		before_last = current;
		current = current->next;
	}
	before_last->next = NULL;
	current->next = first;
	first = current;
	first->next = NULL;
	ft_instructnew(stacks, "ra");
}