/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:40:05 by sma               #+#    #+#             */
/*   Updated: 2021/07/03 17:26:30 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strlen3(char *c)
{
	int		i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

void		ft_strcpy3(char *js, char const *s1, char const *s2)
{
	while (*s1)
		*js++ = *s1++;
	while (*s2)
		*js++ = *s2++;
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*js;
	int		s1len;
	int		s2len;

	if (!s1)
		return ((char *)s1);
	if (!s2)
		return ((char *)s2);
	s1len = ft_strlen3((char*)s1);
	s2len = ft_strlen3((char*)s2);
	if (!(js = (char*)malloc(sizeof(char) * (s1len + s2len + 1))))
		return (NULL);
	js[s1len + s2len] = '\0';
	ft_strcpy3(js, s1, s2);
	return (js);
}
