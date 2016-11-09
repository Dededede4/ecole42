/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:35:43 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/09 11:41:54 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char    *ft_strdup(char *src);

int		main(int argc, char **argv)
{
	char *test = "coucou ceci est un string\n";
	char *test2 = ft_strdup(test);
	printf("%s", test2);
	if (test != test2)
	{
		printf("adressage different");
	}
}
