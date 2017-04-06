/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 20:38:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/28 17:54:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCRIPT_H
# define SCRIPT_H

# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include "../../includes/libft/libft.h"

# define N 32

typedef struct	s_rand
{
	int			tab[N];
	int			first;
}				t_rand;

typedef struct	s_env
{
	t_rand		rd;
	int			fd_res;
	char		*line;
	int			dump;
	int			nb_player;
	int			i_champ;
	char		*chr;
	char		cmd[500];
	int			i;
	int			j;
	int			b;
	int			y;
	int			count;
	char		*str_unit;
	int			nb_test;
}				t_env;

static char	*g_player[50] =
{
	"champ/Asombra.cor",
	"champ/doge.cor",
	"champ/Kappa.cor",
	"champ/dubo.cor",
	"champ/Machine-gun.cor",
	"champ/gedeon.cor",
	"champ/MarineKing.cor",
	"champ/jinx.cor",
	"champ/Misaka_Mikoto.cor",
	"champ/casimir.cor",
	"champ/justin_bee.cor",
	"champ/Rainbow_dash.cor",
	"champ/littlepuppy.cor",
	"champ/THUNDER.cor",
	"champ/live.cor",
	"champ/Varimathras.cor",
	"champ/big_feet.cor",
	"champ/champ.cor",
	"champ/loose.cor",
	"champ/darksasuke.cor",
	"champ/meowluigi.cor",
	"champ/salamahenagalabadoun.cor",
	"champ/sam_2.0.cor",
	"champ/skynet.cor",
	"champ/Wall.cor",
	"champ/terminator.cor",
	"champ/_.cor",
	"champ/helltrain.cor",
	"champ/turtle.cor",
	"champ/_honeybadger.cor",
	"champ/ultimate-surrender.cor",
	"champ/bee_gees.cor",
	"champ/youforkmytralala.cor"
};

void			init_env(t_env *e, char **argv);
int				rd(t_rand *rd);
int				run_test_unit(t_env *e);
int				run_test_all(t_env *e);
int				run_test_rd(t_env *e);

#endif
