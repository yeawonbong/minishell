/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:12:30 by sma               #+#    #+#             */
/*   Updated: 2021/01/10 00:05:09 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char		*temp;
	unsigned char		*srct;
	size_t				i;

	temp = (unsigned char*)dest;
	srct = (unsigned char*)src;
	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	while (i++ < size)
		*temp++ = *srct++;
	return (dest);
}
