/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 08:02:26 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/26 09:26:24 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define SIZE_HH = 1
# define SIZE_H = 2
# define SIZE_L = 3
# define SIZE_LL = 4
# define SIZE_J = 5
# define SIZE_Z = 6


struct		s_flags
{
	char	hash;
	char	zero;
	char	plus;
	char	minus;
	char	space;
	int		width;
	int		precision;
	char	lenght;
	char 	type;
	int		i;
	
}			t_flags;

#endif
