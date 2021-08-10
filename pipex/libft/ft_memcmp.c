/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:08:57 by sma               #+#    #+#             */
/*   Updated: 2020/12/29 00:10:27 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *src1, const void *src2, size_t size)
{
	unsigned char	*sr1;
	unsigned char	*sr2;
	size_t			i;

	sr1 = (unsigned char*)src1;
	sr2 = (unsigned char*)src2;
	i = 0;
	while (i < size)
	{
		if (sr1[i] != sr2[i])
			return (sr1[i] - sr2[i]);
		i++;
	}
	return (0);
}
