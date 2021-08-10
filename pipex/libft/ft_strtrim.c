/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 00:33:05 by sma               #+#    #+#             */
/*   Updated: 2021/01/20 16:43:49 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			isset(char str, char const *set)
{
	while (*set)
	{
		if (str == *set)
			return (1);
		set++;
	}
	return (0);
}

void		ft_setcpy(char *setstr, char const *s1, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		*setstr++ = s1[i];
		i++;
	}
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		begin;
	int		end;
	char	*setstr;

	if (!s1 || !set)
		return (0);
	begin = 0;
	while (s1[begin] && isset(s1[begin], set))
		begin++;
	end = ft_strlen((char*)s1) - 1;
	while (end >= 0 && isset(s1[end], set))
		end--;
	len = end - begin + 1;
	if (len < 0)
		len = 0;
	if (!(setstr = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	setstr[len] = '\0';
	ft_setcpy(setstr, s1 + begin, len);
	return (setstr);
}
