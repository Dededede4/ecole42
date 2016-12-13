/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tetri_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:34:05 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/13 16:31:44 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
int		main(void)
{
	char	command[] = "../fillit ../maps/tetri_01.txt";
	char	result[] = "ABBBB.\nACCCEE\nAFFCEE\nA.FFGG\nHHHDDG\n.HDD.G\n";
	FILE *fp;
	char output[1035];

	/* Open the command for reading. */
	fp = popen(command, "r");
	if (fp == NULL) {
	printf("Failed to run command\n" );
	exit(5);
	}

	/* Read the output a line at a time - output it. */
	fread(output, 1034, 1, fp);
	if (0 != strcmp(output, result))
		return 10;

	/* close */
	pclose(fp);

	return 0;
}
