/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fill_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:29:08 by ybong             #+#    #+#             */
/*   Updated: 2021/09/26 20:17:47 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmds_err(t_data *data, char *buf)
{
	data->cmds = ft_split("", ' ');
	free(buf);
	return (ft_strdup(""));
}

int	non_redirect(t_data *data)
{
	if (check_builtin(data->cmds[data->idx]))
		ft_builtins(data);
	else
	{
		if (exec_in_child(data) == -1)
		{
			split_free(data->cmd_args);
			return (-1);
		}
	}
	return (0);
}

void	get_cmd_arg(t_data *data, int idx)
{
	data->cmd_args = ft_split("", ' ');
	data->cmd_args = ft_split_with(' ', data->cmds[idx], \
											data->cmd_args, data);
}

void	if_pipe_dup2(t_data *data, int fd1, int fd2, int toclose)
{
	if (data->cmds[data->idx + 1] != NULL)
	{
		dup2(fd1, fd2);
		close(toclose);
	}
}

void	ft_filldata(t_data *data, char **envp)
{
	int		i;

	i = 0;
	g_status = 0;
	data->idx = 0;
	data->path = 0;
	data->env_height = ft_strarr_height(envp);
	data->env = (char **)malloc(sizeof(char *) * (data->env_height + 1));
	data->env[data->env_height] = NULL;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	data->stdio[0] = dup(STDIN_FILENO);
	data->stdio[1] = dup(STDOUT_FILENO);
	data->redirect_flag = 0;
	ft_sort_env(data);
	return ;
}
