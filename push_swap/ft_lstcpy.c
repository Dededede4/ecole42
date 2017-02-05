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

t_list	*ft_lstcpy_max(t_list *src, size_t max)
{
	t_list	*first;
	t_list	*current;
	size_t	i;

	first = NULL;
	i = 0;
	while (src && i < max)
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
		i++;
		src = src->next;
	}
	return (first);
}