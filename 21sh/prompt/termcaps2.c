/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 10:19:14 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 10:19:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_bool		t_delete_after_cursor(void)
{
	char	*str;

	str = tgetstr("cd", NULL);
	if (!str)
		return (FALSE);
	tputs(str, ft_strlen(str), ft_putchar2);
	return (TRUE);
}

t_bool		t_start_under(void)
{
	char	*str;

	str = tgetstr("so", NULL);
	if (!str)
		return (FALSE);
	tputs(str, ft_strlen(str), ft_putchar2);
	return (TRUE);
}

t_bool		t_stop_under(void)
{
	char	*str;

	str = tgetstr("se", NULL);
	if (!str)
		return (FALSE);
	tputs(str, ft_strlen(str), ft_putchar2);
	return (TRUE);
}
