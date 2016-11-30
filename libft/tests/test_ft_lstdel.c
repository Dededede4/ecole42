/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:07:36 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/30 14:13:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void    fake_del2(void *content, size_t content_size)
{
	(*(int *)content) = 1000 + content_size;
}

int		main(void)
{
	// merci à dlouise
	int     pid;
	int     status;
	t_list  *lst;
	t_list  *dernier_maillon;
	lst = ft_lstnew("abcdefg", 8);
	lst->next = ft_lstnew("abc", 4);
	lst->next->next = ft_lstnew("ab", 3);
	dernier_maillon = lst->next->next;

	ft_lstdel(&lst->next, fake_del2);

	if (NULL != lst->next)
		return (10);

	pid = fork();
	if (pid) // Pere
	{
		if ( ! (-1 != wait(&status) && WIFSIGNALED(status)))
			return (20);
	}
	else // Fils
	{
		fclose(stderr);
		free(dernier_maillon);
		exit(0);
	}

	return (0);
}
