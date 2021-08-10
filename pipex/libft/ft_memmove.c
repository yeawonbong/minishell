/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:40:33 by sma               #+#    #+#             */
/*   Updated: 2021/01/03 19:12:26 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char	*dst;
	unsigned char	*sr;
	size_t			i;

	dst = (unsigned char*)dest;
	sr = (unsigned char*)src;
	i = 0;
	if (!src && !dest)
		return (0);
	if (dst > sr)
	{
		while (size-- > 0)
			dst[size] = sr[size];
	}
	else
	{
		while (i < size)
		{
			dst[i] = sr[i];
			i++;
		}
	}
	return ((void*)dst);
}
