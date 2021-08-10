/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:16:00 by sma               #+#    #+#             */
/*   Updated: 2021/07/03 17:26:39 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_free(char **ss, int len)
{
	int		i;

	i = 0;
	while (i <= len)
	{
		free(ss[i]);
		i++;
	}
	free(ss);
	return (NULL);
}

int			ft_strcpy2(char **ss, char *str, char c, int idx)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (!(ss[idx] = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (*str != c && *str != '\0')
	{
		ss[idx][i] = *str;
		str++;
		i++;
	}
	ss[idx][i] = '\0';
	return (1);
}

int			ft_count(char *str, char c)
{
	int		i;
	int		count;
	int		flag;

	i = 0;
	count = 1;
	flag = 1;
	if (!(*str))
		return (0);
	while (str[i])
	{
		if (str[i] == c && i > 0 && flag == 0)
		{
			count++;
			flag = 1;
		}
		else if (str[i] != c)
			flag = 0;
		i++;
	}
	if (str[i - 1] == c)
		count--;
	return (count);
}

char		**ft_split(char *str, char c)
{
	int		i;
	int		count;
	char	**ss;

	if (!str)
		return (NULL);
	i = 0;
	count = ft_count(str, c);
	if (!(ss = (char**)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	ss[count] = NULL;
	while (i < count)
	{
		while (*str == c)
			str++;
		if (ft_strcpy2(ss, str, c, i) == 0)
			return (ft_free(ss, i));
		while (*str != c && *str != '\0')
			str++;
		i++;
	}
	return (ss);
}
