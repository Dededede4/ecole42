/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:28:37 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 19:28:47 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int		heredoc(char *stop)
{
	char	*str;
	int		p[2];

	pipe(p);
	str = display_input_heredoc(stop);
	free(stop);
	ft_putstr_fd(str, p[1]);
	ft_strdel(&str);
	close(p[1]);
	return (p[0]);
}
