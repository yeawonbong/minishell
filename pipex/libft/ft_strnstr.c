/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:47:06 by sma               #+#    #+#             */
/*   Updated: 2021/01/22 02:12:11 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr2(const char *str2, const char *find, size_t i, size_t j)
{
	size_t	s;
	size_t	f;
	size_t	count;

	s = 0;
	while (s <= i - j && s < i && str2[s] != '\0')
	{
		count = 0;
		f = 0;
		while (f < j && str2[s + f] != '\0')
		{
			if (str2[s + f] == find[f])
			{
				count++;
				if (count == j)
					return ((char*)&str2[s]);
			}
			f++;
		}
		s++;
	}
	return (0);
}

char		*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*to_find)
		return ((char*)str);
	while (to_find[j] != '\0')
		j++;
	return ((char*)ft_strnstr2(str, to_find, size, j));
}
