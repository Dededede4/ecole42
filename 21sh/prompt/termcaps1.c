/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 10:15:06 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 10:15:08 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_bool		t_enable_insert_mode(void)
{
	char	*str;

	str = tgetstr("im", NULL);
	if (!str)
		return (FALSE);
	tputs(str, ft_strlen(str), ft_putchar2);
	return (TRUE);
}

t_bool		t_disable_insert_mode(void)
{
	char	*str;

	str = tgetstr("ei", NULL);
	if (!str)
		return (FALSE);
	tputs(str, ft_strlen(str), ft_putchar2);
	return (TRUE);
}

t_bool		t_move_left(void)
{
	char	*str;

	str = tgetstr("le", NULL);
	if (!str)
	{
		ft_printf("\nBINGO !\n");
		return (FALSE);
	}
	tputs(str, ft_strlen(str), ft_putchar2);
	return (TRUE);
}

t_bool		t_move_right(void)
{
	char	*str;

	str = tgetstr("nd", NULL);
	if (!str)
		return (FALSE);
	tputs(str, ft_strlen(str), ft_putchar2);
	return (TRUE);
}

t_bool		t_delete_last_char(void)
{
	char	*str;

	str = tgetstr("dc", NULL);
	if (!str)
	{
		ft_printf("\nBINGO2 !\n");
		return (FALSE);
	}
	if (!str)
		return (FALSE);
	t_move_left();
	tputs(str, ft_strlen(str), ft_putchar2);
	return (TRUE);
}
