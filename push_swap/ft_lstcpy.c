#include "push_swap.h"


t_list	*ft_lstcpy(t_list *src)
{
	t_list	*first;
	t_list	*current;


	first = NULL;
	while (src)
	{
		if (first == NULL)
		{
			first = ft_lstnew(src->content, src->content_size);
			current = first;
		}
		else
		{
			current->next = ft_lstnew(src->content, src->content_size);
			current = current->next;
		}
		src = src->next;
	}
	return (first);
}