/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 01:38:18 by ybong             #+#    #+#             */
/*   Updated: 2021/08/10 00:35:11 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_height(char const *s, char c)
{
	int		count;

	count = 0;
	if (*s != c && *s)
		count++;
	s = ft_strchr(s, (int)c);
	while (s && *s)
	{
		if (s[1] && s[1] != c)
			count++;
		s++;
		s = ft_strchr(s, (int)c);
	}
	return (count);
}

static int	ft_count_width(char const *s, char c)
{
	int		count;

	count = 0;
	while (*s)
	{
		s++;
		count++;
		if (*s == c)
			break ;
	}
	return (count);
}

static char	ft_fill_arr(char const *s, char c, int i, char **arr)
{
	int	j;

	j = 0;
	while (!(s[j] == c) && s[j])
	{
		arr[i][j] = s[j];
		j++;
	}
	arr[i][j] = '\0';
	return (0);
}

static char	**ft_free_mem(char **arr, int current)
{
	int	i;

	i = 0;
	while (i < current)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		height;
	int		i;

	if (!s)
		return (0);
	height = ft_count_height(s, c);
	arr = (char **)malloc(sizeof(char *) * (height + 1));
	if (!(arr))
		return (0);
	arr[height] = NULL;
	i = 0;
	while (i < height)
	{
		while (*s == c)
			s++;
		arr[i] = malloc(sizeof(char) * (ft_count_width(s, c) + 1));
		if (!arr[i])
			return (ft_free_mem(arr, i));
		ft_fill_arr(s, c, i, arr);
		if (ft_strchr(s, (int)c))
			s = ft_strchr(s, (int)c);
		i++;
	}
	return (arr);
}

// char		**ft_free(char **ss, int len)
// {
// 	int		i;

// 	i = 0;
// 	while (i <= len)
// 	{
// 		free(ss[i]);
// 		i++;
// 	}
// 	free(ss);
// 	return (NULL);
// }

// int			ft_strcpy2(char **ss, char *str, char c, int idx)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i] != c && str[i] != '\0')
// 		i++;
// 	if (!(ss[idx] = (char*)malloc(sizeof(char) * (i + 1))))
// 		return (0);
// 	i = 0;
// 	while (*str != c && *str != '\0')
// 	{
// 		ss[idx][i] = *str;
// 		str++;
// 		i++;
// 	}
// 	ss[idx][i] = '\0';
// 	return (1);
// }

// int			ft_count(char *str, char c)
// {
// 	int		i;
// 	int		count;
// 	int		flag;

// 	i = 0;
// 	count = 1;
// 	flag = 1;
// 	if (!(*str))
// 		return (0);
// 	while (str[i])
// 	{
// 		if (str[i] == c && i > 0 && flag == 0)
// 		{
// 			count++;
// 			flag = 1;
// 		}
// 		else if (str[i] != c)
// 			flag = 0;
// 		i++;
// 	}
// 	if (str[i - 1] == c)
// 		count--;
// 	return (count);
// }

// char		**ft_split(char *str, char c)
// {
// 	int		i;
// 	int		count;
// 	char	**ss;

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	count = ft_count(str, c);
// 	if (!(ss = (char**)malloc(sizeof(char*) * (count + 1))))
// 		return (NULL);
// 	ss[count] = NULL;
// 	while (i < count)
// 	{
// 		while (*str == c)
// 			str++;
// 		if (ft_strcpy2(ss, str, c, i) == 0)
// 			return (ft_free(ss, i));
// 		while (*str != c && *str != '\0')
// 			str++;
// 		i++;
// 	}
// 	return (ss);
// }
