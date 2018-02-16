/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 10:38:18 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/13 10:38:20 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	sig_handler(int signo)
{
	extern char **environ;

	if (signo == SIGINT)
	{
	}
	if (signo == SIGQUIT || signo == SIGTERM)
	{
		execve("/usr/bin/reset", (char *[15]){"/usr/bin/reset"}, environ);
	}
}
