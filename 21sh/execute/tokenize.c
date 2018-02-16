/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 22:43:38 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 22:43:48 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_token		*get_next(t_token *token, t_token **first_token)
{
	if (NULL == token)
	{
		token = ft_memalloc(sizeof(*token));
		*first_token = token;
	}
	else
	{
		token->next = ft_memalloc(sizeof(*token));
		token = token->next;
	}
	return (token);
}

t_token		*tokenize(unsigned int *str)
{
	int				i;
	size_t			stop;
	t_token			*token;
	t_token			*first_token;

	i = -1;
	token = NULL;
	first_token = NULL;
	if (!str || !*str)
		return (NULL);
	while (++i < (int)ft_uintlen(str))
	{
		if (' ' != str[i] && '\t' != str[i])
		{
			stop = get_word_pos(str, i);
			token = get_next(token, &first_token);
			token->str = (unsigned int *)
				ft_memdup(((char*)str) + (i * 4), (stop - i + 1) * 4);
			token->str = ft_uinttrim_free(&(token->str));
			token->str = clear_escapes(token->str);
			i = stop;
		}
	}
	return (first_token);
}
