/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy2_spec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 17:40:43 by heynard           #+#    #+#             */
/*   Updated: 2017/06/22 17:40:46 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy2_spec(char *dst, const char *src, char spec)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && src[i] != spec)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
