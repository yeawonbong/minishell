/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:39:13 by sma               #+#    #+#             */
/*   Updated: 2020/12/28 23:39:29 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dest, const void *src, int c, size_t size)
{
	unsigned char	*dst;
	unsigned char	*sr;
	size_t			i;

	dst = (unsigned char*)dest;
	sr = (unsigned char*)src;
	i = 0;
	while (i < size)
	{
		dst[i] = sr[i];
		if ((unsigned char)c == sr[i])
			return ((void*)dst + i + 1);
		i++;
	}
	return (0);
}
