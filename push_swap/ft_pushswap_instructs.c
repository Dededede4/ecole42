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
	while (current->next)
		current = current->next;
	stacks->stacka = first->next;
	current->next = first;
	first->next = NULL;
	ft_instructnew(stacks, "ra");
}

void		ft_pushswap_rb(t_stacks *stacks)
{
	t_vals	*first;
	t_vals	*current;

	if (stacks->stacka->next == NULL)
		return ;
	first = stacks->stackb;
	current = first;
	while (current->next)
		current = current->next;
	stacks->stackb = first->next;
	current->next = first;
	first->next = NULL;
	ft_instructnew(stacks, "rb");
}

void		ft_pushswap_rra(t_stacks *stacks)
{
	t_vals	*first;
	t_vals	*current;
	t_vals	*before_last;

	if (stacks->stacka->next == NULL)
		return ;
	first = stacks->stacka;
	current = first;
	while (current->next)
	{
		before_last = current;
		current = current->next;
	}
	current->next = first;
	stacks->stacka = current;
	before_last->next = NULL;
	ft_instructnew(stacks, "rra");
}

void		ft_pushswap_rrb(t_stacks *stacks)
{
	t_vals	*first;
	t_vals	*current;
	t_vals	*before_last;

	if (stacks->stackb->next == NULL)
		return ;
	first = stacks->stackb;
	current = first;
	while (current->next)
	{
		before_last = current;
		current = current->next;
	}
	current->next = first;
	stacks->stackb = current;
	before_last->next = NULL;
	ft_instructnew(stacks, "rrb");
}

void		ft_pushswap_instruct(char instruct, t_stacks *stacks)
{
	if (instruct == INSTRUCT_SA)
		ft_pushswap_sa(stacks);
	else if (instruct == INSTRUCT_SB)
		ft_pushswap_sb(stacks);
	else if (instruct == INSTRUCT_SS)
		ft_pushswap_ss(stacks);
	else if (instruct == INSTRUCT_PA)
		ft_pushswap_pa(stacks);
	else if (instruct == INSTRUCT_PB)
		ft_pushswap_pb(stacks);
	else if (instruct == INSTRUCT_RA)
		ft_pushswap_ra(stacks);
	else if (instruct == INSTRUCT_RB)
		ft_pushswap_rb(stacks);
	else if (instruct == INSTRUCT_RRA)
		ft_pushswap_rra(stacks);
	else if (instruct == INSTRUCT_RRB)
		ft_pushswap_rrb(stacks);
	else
	{
		ft_putstr_fd("Error : ft_pushswap_instruct have unknown instruction.", 1);
		exit(1);
	}

}