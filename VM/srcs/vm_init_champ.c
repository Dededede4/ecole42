/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 04:16:24 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/28 17:57:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			vm_size_champ(t_champ *champ, t_datas *datas)
{
	int size;
	int save;
	int cur;

	size = 0;
	cur = (int)champ->champ[size];
	while (cur >= 1 && cur < NBR_FONC)
	{
		save = size;
		if (vm_have_ocp(cur))
		{
			size += vm_ocp_size(champ->champ[size + 1], 3,
					datas->op_tab[cur].nbr_octet_dir) % MEM_SIZE;
			size += 2;
		}
		else
			size += (vm_havent_ocp(cur) % MEM_SIZE) + 1;
		cur = (int)champ->champ[size];
	}
	return (size);
}

int					vm_inv_octets(unsigned int champion)
{
	char	c[4];
	int		i;

	i = 3;
	while (champion)
	{
		c[i] = champion & 0xff;
		champion >>= 8;
		--i;
	}
	return (*(int *)c);
}

static void			vm_verif_champ(char *chmp_info, t_champ *champ, int j)
{
	int				i;
	unsigned char	*c;
	t_header		*champion;

	c = (unsigned char*)chmp_info;
	i = COREWAR_EXEC_MAGIC;
	if (c[0] == (i >> 24) && c[1] == ((i >> 16) & 0xff)
			&& c[2] == ((i >> 8) & 0xff) && c[3] == (i & 0xff))
		;
	else
		exit(ft_int_error("magic exec invalide"));
	champion = (t_header *)&chmp_info[0];
	if (vm_inv_octets(champion->prog_size) != j - sizeof(t_header) ||
		j - sizeof(t_header) > CHAMP_MAX_SIZE)
	{
		ft_printf("sizes give %#x size find %#x\n",
							vm_inv_octets(champion->prog_size),
							j - sizeof(t_header));
		exit(ft_int_error("chamion size incorrect"));
	}
	ft_memcpy(champ->champ_name, chmp_info + 4, PROG_NAME_LENGTH);
}

static void			vm_create_champ(t_champ *champs, char *entry, int i,
		t_datas *datas)
{
	int					fd;
	int					j;
	char				buff[sizeof(t_header) + CHAMP_MAX_SIZE + 1];

	if (1 > (fd = open(entry, O_RDONLY)))
		exit(ft_int_error("Echec de lecture du champion"));
	if ((j = read(fd, &buff, sizeof(t_header) + CHAMP_MAX_SIZE + 1)) == -1
		|| j < (int)sizeof(t_header) + 1)
		exit(ft_int_error("Echec de read du champion"));
	buff[sizeof(t_header) + CHAMP_MAX_SIZE] = 0;
	vm_verif_champ(buff, &champs[i], j);
	ft_memcpy((void *)&champs[i], (void *)(buff + sizeof(t_header)),
			j - sizeof(t_header));
	(!champs[i].champ_nbr) ? (champs[i].champ_nbr = -(i + 1)) : 0;
	champs[i].champ_size = vm_size_champ(&champs[i], datas);
	if (close(fd) == -1)
		exit(ft_int_error("Echec de close du champion"));
	ft_memcpy(champs[i].champ_com, &buff[4 + PROG_NAME_LENGTH + 8],
														COMMENT_LENGTH);
}

int					vm_init_champ(t_champ *champs, int argc, char **argv,
		t_datas *datas)
{
	int		champ_nbr;
	int		i;

	i = datas->player_nbr;
	champ_nbr = 0;
	while (i < argc && argv[i])
	{
		if (!ft_strcmp(argv[i], "-n"))
		{
			if (argv[i + 1] && ft_isatoied(argv[i + 1]) != -1)
				((champs[champ_nbr].champ_nbr = ft_atoi(argv[i + 1])) == 0) ?
				exit(ft_int_error("Champ number 0 are forbiden !"))
				: 0;
			else
				exit(ft_int_error("Number format invalide !"));
			i += 2;
		}
		vm_create_champ(champs, argv[i], champ_nbr, datas);
		++i;
		if (++champ_nbr > MAX_PLAYERS)
			exit(ft_int_error("Too many champs"));
	}
	return (champ_nbr);
}
