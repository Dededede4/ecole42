#include "push_swap.h"

void 	ft_lstadd_end(t_list **lst, t_list *new)
{
	t_list	*current;
	if (lst == NULL || new == NULL)
		return ;
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;

}