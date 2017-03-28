/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 04:00:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/28 14:28:14 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		vm_verif_arg(int argc)
{
	if (argc == 1)
	{
		ft_printf("./corewar [-h nbr_cycles] [-m -b -v] [-dump nbr_cycles]");
		ft_printf(" [[-n number] champion1.cor] ...\n");
		exit(0);
	}
}

static int		vm_end_main(t_datas *datas)
{
	if (datas->flag & FLAG_K && datas->flag & FLAG_M)
		corewar_end_music(datas, 1);
	return (0);
}

static void		recup_data_size_arena(t_datas *datas)
{
	datas->nc.size_max_y = (ft_gcd(MEM_SIZE) + 2);
	datas->nc.size_max_x = (ft_gcd(MEM_SIZE) * 3 + 2);
}

int				main(int argc, char **argv)
{
	t_lives		lives;
	t_champ		champs[MAX_PLAYERS + 1];
	t_datas		datas;

	vm_verif_arg(argc);
	vm_verif_macro();
	vm_innit_to_0(&datas, champs, &lives);
	vm_champ_process(&datas, argc, argv);
	vm_print_start_battle(&datas);
	recup_data_size_arena(&datas);
	if (datas.flag & FLAG_M)
		ncurses_init(&datas, datas.nc.size_max_y, datas.nc.size_max_x + 1);
	if (datas.flag & FLAG_K && datas.flag & FLAG_M)
		corewar_music(&datas, 1, vm_init_process);
	else
		vm_init_process(&datas);
	if (datas.flag & FLAG_M)
	{
		ncurses_print_end(&datas);
		ncurses_end(&datas);
	}
	if (datas.end)
		vm_print_end_battle(&datas);
	vm_destroy_all_process(&datas);
	return (vm_end_main(&datas));
}
