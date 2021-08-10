/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:45:12 by sma               #+#    #+#             */
/*   Updated: 2021/01/01 03:47:53 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!dest || !src)
		return (0);
	while (src[i])
		i++;
	if (size != 0)
	{
		while (j < size - 1 && src[j])
		{
			dest[j] = src[j];
			++j;
		}
		dest[j] = '\0';
	}
	return (i);
}
