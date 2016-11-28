/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 11:02:18 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 11:25:20 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	str[] = "naaa naaaan je ne veux pas mourir ! :'(";
	void	*test = strdup(str);
	ft_memdel((void*)test);
	return (0);
}
