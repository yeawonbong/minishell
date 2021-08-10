/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:46:34 by sma               #+#    #+#             */
/*   Updated: 2021/07/03 17:28:14 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && !(dest[i] == '\0' && src[i] == '\0'))
	{
		if (dest[i] != src[i])
			return ((unsigned char)dest[i] - (unsigned char)src[i]);
		i++;
	}
	return (0);
}
