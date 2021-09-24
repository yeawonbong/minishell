/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:45:39 by sma               #+#    #+#             */
/*   Updated: 2021/09/24 16:31:43 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char *temp)
{
	int		i;
	char	q;

	i = 0;
	q = 0;
	while (temp[i])
	{
		if (temp[i] == '\'' || temp[i] == '"')
		{
			if (q == 0)
				q = temp[i];
			else if (temp[i] == q)
				q = 0;
		}
		if (ft_strchr("<>", temp[i]) && q == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**add_str(char **arr, char *toadd, t_data *data, char c)
{
	int		i;
	char	**temp;

	i = 0;
	while (arr[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (arr[++i])
		temp[i] = ft_strdup(arr[i]);
	temp[i] = ft_strtrim(toadd, "\t ");
	if (c == '|')
	{
		if (check_redir(temp[i]))
			data->redirect_flag++;
		if (ft_strchr(temp[i], '$') || ft_strchr(temp[i], '\'') \
		|| ft_strchr(temp[i], '"'))
			temp[i] = ft_modify_buf(data, temp[i]);
	}
	temp[i + 1] = NULL;
	free(toadd);
	ft_split_free(arr);
	return (temp);
}

static char	check_quote(char *newbuf, int i, char quote)
{
	if (quote == 0)
		quote = *(newbuf + i);
	else if (*(newbuf + i) == quote)
		quote = 0;
	return (quote);
}

char	**ft_split_with(char c, char *buf, char **arr, t_data *data)
{
	char	*newbuf;
	int		i;
	char	quote;

	newbuf = buf;
	i = 0;
	quote = 0;
	while (*(newbuf + i))
	{
		if (*(newbuf + i) == '\'' || *(newbuf + i) == '"')
			quote = check_quote(newbuf, i, quote);
		if (*(newbuf + i) == c)
		{
			if (quote == 0)
			{
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
