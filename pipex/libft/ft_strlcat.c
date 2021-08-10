/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:44:10 by sma               #+#    #+#             */
/*   Updated: 2021/01/22 20:07:58 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t			i;
	size_t			dstlen;
	size_t			srclen;
	size_t			endidx;

	dstlen = ft_strlen(dest);
	srclen = ft_strlen((char*)src);
	i = 0;
	endidx = dstlen;
	if (size == 0)
		return (srclen);
	if (size <= dstlen)
		return (size + srclen);
	while ((i + dstlen + 1 < size) && (src[i] != '\0'))
	{
		dest[endidx] = src[i];
		i++;
		endidx++;
	}
	dest[endidx] = '\0';
	return (dstlen + srclen);
}
