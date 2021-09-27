/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:45:39 by sma               #+#    #+#             */
/*   Updated: 2021/09/27 16:12:18 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (c == ' ')
	{
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

char	**pipe_error(char **arr)
{
	split_free(arr);
	printf("minish: syntax error near unexpected token '|'\n");
	g_status = 258;
	return (0);
}

void	init_q(t_qte *q, char *buf)
{
	q->newbuf = buf;
	q->i = 0;
	q->quote = 0;
}

char	**ft_split_with(char c, char *buf, char **arr, t_data *data)
{
	t_qte	q;

	init_q(&q, buf);
	while (*(q.newbuf + q.i))
	{
		if (*(q.newbuf + q.i) == '\'' || *(q.newbuf + q.i) == '"')
			q.quote = check_quote(q.newbuf, q.i, q.quote);
		if (*(q.newbuf + q.i) == c)
		{
			if (q.quote == 0)
			{
				if (0 < q.i)
					arr = add_str(arr, ft_substr(q.newbuf, 0, q.i), data, c);
				if (c == '|' && *(q.newbuf + (q.i + 1)) == 0)
					return (pipe_error(arr));
				q.newbuf += (q.i + 1);
				q.i = -1;
			}
		}
		q.i++;
	}
	arr = add_str(arr, ft_substr(q.newbuf, 0, q.i), data, c);
	return (arr);
}
