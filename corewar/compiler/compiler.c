/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 14:06:53 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/05 14:07:19 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shared/op.h"
#include "../shared/libft/libft.h"

void error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(0);
}

char *get_output_path(char *name)
{
	char	*output_path;
	char	*tmp;

	tmp = ft_strrchr(name, '.');
	if (!tmp)
		return (ft_strdup(".s"));
	*tmp = '\0';
	return (ft_strjoin_multi(FALSE, name, ".s", NULL));
}

void	write_exec_magic(int fd)
{
	int nbr;
	int revnbr;
	int i;
	int size;

	i = 3;
	nbr = COREWAR_EXEC_MAGIC;
	//write(fd, &nbr, 4);
	revnbr = 0;
	while (i >= 0)
	{
		((char*)(&revnbr))[i] = ((char*)(&nbr))[0];
		ft_printf("%x, %x\n", revnbr, nbr);
		//revnbr = revnbr << 8;
		nbr = nbr >> 8;
		i--;
	}
	write(fd, &revnbr, 4);
}

int main(int argc, char **argv)
{
	char	*output_path;
	int		fd;

	if (argc != 2)
		error("Usage : ./asm mychampion.s\n");
	output_path = get_output_path(argv[1]);
	fd = open(output_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	write_exec_magic(fd);
	//ft_putstr_fd("Hey !\n", fd);
	exit(0);
	return (0);
}