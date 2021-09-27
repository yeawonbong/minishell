/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:29 by ybong             #+#    #+#             */
/*   Updated: 2021/09/27 16:12:36 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_strjoin_free(char *dest, char *src)
{
	char	*temp;

	temp = dest;
	dest = ft_strjoin(temp, src);
	free(temp);
	return (dest);
}

static	int	redir_exec(t_data *data, t_re *re)
{
	int		i;
	pid_t	pid;
	int		error;

	i = 0;
	pid = 0;
	while (i < re->re_argc)
	{
		if (re->re_type[i] == 1)
			error = redir_1(data, re->re_file[i]);
		else if (re->re_type[i] == 2)
			error = redir_2(data, re->re_file[i]);
		else if (re->re_type[i] == 3)
			error = redir_3(data, re->re_file[i]);
		else if (re->re_type[i] == 4)
			error = redir_4(re->re_file[i], data);
		if (error == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	redirect(t_data *data, int idx)
{
	t_re	re;

	join_cmds(data, idx);
	if (get_redirect(data->cmds[idx], &re) == -1)
	{
		free(re.cmd_j);
		g_status = 258;
		return (-1);
	}
	free(data->cmds[idx]);
	data->cmds[idx] = re.cmd_j;
	get_cmd_arg(data, idx);
	if (redir_exec(data, &re) == -1)
		return (re_exec_err(data, &re));
	ft_split_free(re.re_file);
	free(re.re_type);
	if (check_builtin(data->cmds[data->idx]))
		ft_builtins(data);
	else
		return (non_builtin(data));
	return (0);
}
