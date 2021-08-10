/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:43:04 by sma               #+#    #+#             */
/*   Updated: 2020/12/29 17:36:28 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			strlen3(const char *src)
{
	int		i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char		*ft_strcpy(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strdup(const char *src)
{
	char	*msrc;
	int		srclen;
	int		i;

	srclen = strlen3(src);
	msrc = (char*)malloc(sizeof(char) * srclen + 1);
	if (msrc == 0)
		return (0);
	i = 0;
	msrc = ft_strcpy(msrc, src);
	return (&msrc[0]);
}
