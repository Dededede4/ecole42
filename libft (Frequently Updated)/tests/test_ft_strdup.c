/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strdup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:14:58 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/14 16:25:43 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../libft.h"

int		main(void)
{
	char	str1[] = "ceci est là et là est icicicauirteuainretauinrset";

	char	*str2 = ft_strdup(str1);

	return strcmp(str2, str1);
}
