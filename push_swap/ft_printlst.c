#include "push_swap.h"

void	ft_printlst_item(t_list *lst)
{
	ft_printf("%d ", *((int*)lst->content));
}

void	ft_printlst_item_str(t_list *lst)
{
	ft_printf("%s\n", ((char*)lst->content));
}

void	ft_printlst(t_list *lst)
{
	ft_lstiter(lst, ft_printlst_item);
}

void	ft_printlst_str(t_list *lst)
{
	ft_lstiter(lst, ft_printlst_item_str);
}