/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:45:39 by sma               #+#    #+#             */
/*   Updated: 2021/09/23 17:18:03 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **add_str(char **arr, char *toadd)
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
	free(toadd);
	temp[i + 1] = NULL;
	// free(arr);
	return (temp);
}

char	**ft_split_with(char c, char *buf, char **arr)
{
	char    *newbuf;
	int     i;
	char		quote;

	newbuf = buf;
	i = 0;
	quote = 0;
	while(*(newbuf + i))//ft_strchr(newbuf, c))
	{printf("newbuf=%s\n", newbuf);
		if (*(newbuf + i) == '\'' || *(newbuf + i) == '"')
		{
			if (quote == 0)
				quote = *(newbuf + i);
			else if (*(newbuf + i) == quote)
				quote = 0;
		}
		if ((*(newbuf + i) == c && quote == 0))
		{//arr 말록된 상태로 들어와야 함.
			if (quote == 0)
				arr = add_str(arr, ft_substr(newbuf, 0, i));
			if (*(newbuf + (i + 1)))
				newbuf += (i + 1);
			i = -1;
		}
		i++;
	}
	arr = add_str(arr, ft_substr(newbuf, 0, i));
	return (arr);
}