/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envtools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 21:43:30 by mprevot           #+#    #+#             */
/*   Updated: 2017/08/10 21:44:08 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_loadenv(char **environ)
{
	int i;

	i = 0;
	while (environ[i])
	{
		ft_putenv(environ[i]);
		i++;
	}
}

int			ft_countenv(void)
{
	t_env	*env;
	t_env	*current;
	int		i;

	i = 0;
	env = *(ft_env());
	current = env;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char		**ft_getpcur(void)
{
	char	**pcur;
	t_env	*env;
	t_env	*current;
	int		i;

	i = 0;
	pcur = ft_memalloc(sizeof(pcur) * (ft_countenv() + 1));
	env = *(ft_env());
	current = env;
	while (current)
	{
		pcur[i] = ft_strjoin_multi(
			FALSE, current->key, "=", current->value, NULL);
		i++;
		current = current->next;
	}
	return (pcur);
}
