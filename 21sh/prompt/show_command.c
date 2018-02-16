/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 10:35:07 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/13 10:35:12 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	show_command(t_command *command)
{
	if (command->str == NULL)
		return ;
	ft_uintput(command->str);
	command->pos = ft_uintlen(command->str);
}
