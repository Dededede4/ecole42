/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memcmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:29:40 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/29 17:02:56 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	str1[] = "aaaaaaa";
	char	str2[] = "bb";
	char	str3[] = "bb";

	if (ft_memcmp(str1, str2, 7) >= 0)
		return (10);

	if (ft_memcmp(str2, str1, 7) <= 0)
		return (20);

	if (ft_memcmp(str2, str3, 2) != 0)
		return (30);
	

	// tests de dlouise
	char    tab1[5];
	char    tab2[5];
	if (0 != ft_memcmp("abcdefghij", "abcdefghij", 10))
		return (40);
	if (0 != memcmp("abcdefghijK", "abcdefghijR", 10))
		return (50);
	if (0 == ft_memcmp("abcdefghij", "abcdefghik", 10))
		return (60);
	if (0 <= ft_memcmp("abcd", "abcz", 4))
		return (70);
	if (0 >= ft_memcmp("abz", "abc", 3))
		return (80);
	if (0 >= ft_memcmp("zab", "aab", 3))
		return (90);
	if (0 != ft_memcmp(NULL, NULL, 0))
		return (100);
	if (0 != ft_memcmp("", "", 1))
		return (110);
	if (0 >= ft_memcmp("\200", "\0", 1))
		return (120);

	strcpy(tab1, "abcd");
	strcpy(tab2, "abde");
	ft_memcmp(tab1, tab2, 5);
	if (0 != strcmp(tab1, "abcd") || 0 != strcmp(tab2, "abde"))
		return (130);

	return (0);
}
