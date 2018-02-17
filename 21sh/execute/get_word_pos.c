/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 22:28:59 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/15 22:29:06 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

size_t	get_word_pos(unsigned int *str, size_t start)
{
	size_t	i;
	char	quote;

	i = start;
	quote = '\0';
	while (str[i])
	{
		if ('\'' == str[i] || '"' == str[i])
		{
			if (!(i > 0 && '\\' == str[i - 1]) && '\0' == quote)
				quote = str[i];
			else if (!(i > 0 && '\\' == str[i - 1]) && (char)str[i] == quote)
				quote = '\0';
		}
		if ('\t' == str[i + 1] || ' ' == str[i + 1] || ';' == str[i + 1] ||
			'>' == str[i + 1] || '<' == str[i + 1] || '|' == str[i + 1])
			if (!quote)
				return (i);
		if ('\t' == str[i] || ' ' == str[i] || ';' == str[i] || '>' == str[i] ||
			'<' == str[i] || '|' == str[i])
			if (!quote)
				return (i);
		i++;
	}
	return (i);
}
