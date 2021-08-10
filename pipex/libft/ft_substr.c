/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:27:26 by sma               #+#    #+#             */
/*   Updated: 2021/01/02 02:00:55 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ftstrlen(char const *s)
{
	int				i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void				ftstrcpy(char *substr, char const *s, size_t size)
{
	while (size-- && *s)
		*substr++ = *s++;
	*substr = '\0';
}

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	size;

	if (!s)
		return (0);
	if (!(substr = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	size = ftstrlen(s);
	if (start >= size)
	{
		substr[0] = 0;
		return (substr);
	}
	ftstrcpy(substr, s + start, len);
	return (substr);
}
