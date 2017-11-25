/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loadenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 12:08:36 by mprevot           #+#    #+#             */
/*   Updated: 2017/08/10 21:29:07 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env		**ft_env(void)
{
	static t_env	*l = NULL;

	return (&l);
}

t_bool		ft_setenvempty(char *name, char *value)
{
	t_env	**root;
	t_env	*env;

	if (!(*(root = ft_env())))
	{
		env = ft_memalloc(sizeof(t_env));
		env->key = ft_strdup(name);
		env->value = ft_strdup(value);
		*root = env;
		return (TRUE);
	}
	return (FALSE);
}

void		ft_setenv(char *name, char *value, int overwrite)
{
	t_env	*env;

	if (ft_setenvempty(name, value))
		return ;
	env = *ft_env();
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0 && 0 == overwrite)
			return ;
		if (ft_strcmp(env->key, name) == 0)
		{
			ft_strdel(&env->value);
			env->value = ft_strdup(value);
			return ;
		}
		if (NULL == env->next)
		{
			env->next = ft_memalloc(sizeof(t_env));
			env->next->key = ft_strdup(name);
			env->next->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

void		ft_delenv(char *name)
{
	t_env *env;
	t_env *prev;
	t_env *tmp;

	env = *(ft_env());
	prev = NULL;
	tmp = NULL;
	while (env)
	{
		if (ft_strequ(name, env->key))
		{
			if (!prev)
				tmp = env->next;
			else
				prev->next = env->next;
			ft_strdel(&env->key);
			ft_strdel(&env->value);
			ft_memdel((void**)&env);
			*(ft_env()) = (tmp) ? tmp : *(ft_env());
			return ;
		}
		prev = env;
		env = env->next;
	}
}

void		ft_delallenv(void)
{
	t_env *env;
	t_env *next;

	env = *(ft_env());
	while (env)
	{
		next = env->next;
		ft_strdel(&env->key);
		ft_strdel(&env->value);
		ft_memdel((void**)&env);
		env = next;
	}
}
