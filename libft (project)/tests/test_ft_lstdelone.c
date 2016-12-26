/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstdelone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:07:51 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/30 13:40:28 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void    fake_del(void *content, size_t content_size)
{
	(*(int *)content) = 1000 + content_size;
}

int		main(void)
{
	// merci à dlouise
	t_list  *maillon;
	t_list  *pmaillon;
	void    *maillon_content;
	int pid;
	int status;


	maillon = ft_lstnew("abcdefg", 8);
	pmaillon = maillon;
	maillon->next = (void*)1; // Fait volontairement planter si on libere next
	maillon_content = maillon->content;

	ft_lstdelone(&pmaillon, fake_del);
	if (1008 != *(int *)maillon_content)
		return (10);

	if (NULL != pmaillon)
		return (20);

	pid = fork();
	if (pid) // Pere
	{
		if ( ! (-1 != wait(&status) && WIFSIGNALED(status)))
			return (30);
	}
	else // Fils
	{
		fclose(stderr);
		free(maillon);
		exit(0);
	}

	return (0);
}
