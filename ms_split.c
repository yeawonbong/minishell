/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:45:39 by sma               #+#    #+#             */
/*   Updated: 2021/09/24 15:49:13 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **add_str(char **arr, char *toadd, t_data *data, char c)
{
	int     i;
	char    **temp;

	i = 0;
	while (arr[i])
		i++;
	temp = (char**)malloc(sizeof(char*) * (i + 2));
	i = 0;
	while(arr[i])
	{	
		temp[i] = ft_strdup(arr[i]);
		i++;
	}
	temp[i] = ft_strtrim(toadd, "\t ");
	if (c == '|' && (ft_strchr(temp[i], '$') || ft_strchr(temp[i], '\'') || ft_strchr(temp[i], '"')))
		temp[i] = ft_modify_buf(data, temp[i]);
	temp[i + 1] = NULL;
	free(toadd);
	ft_split_free(arr);
	return (temp);
}

char	**ft_split_with(char c, char *buf, char **arr, t_data *data)
{
	char    *newbuf;
	int     i;
	char	quote;
	char	*tempstr;

	newbuf = buf;
	i = 0;
	quote = 0;
	while(*(newbuf + i))//ft_strchr(newbuf, c))
	{
		if (*(newbuf + i) == '\'' || *(newbuf + i) == '"')
		{
			if (quote == 0)
				quote = *(newbuf + i);
			else if (*(newbuf + i) == quote)
				quote = 0;
		}
		if (*(newbuf + i) == c)
		{
			if (quote == 0)
			{
				tempstr = ft_substr(newbuf, 0, i);
				arr = add_str(arr, ft_substr(newbuf, 0, i), data, c);
				if (*(newbuf + (i + 1)))
					newbuf += (i + 1);
				i = -1;
			}
		}
		i++;
	}
	arr = add_str(arr, ft_substr(newbuf, 0, i), data, c);
	return (arr);
}
