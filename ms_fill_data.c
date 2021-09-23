/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fill_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:29:08 by ybong             #+#    #+#             */
/*   Updated: 2021/09/20 19:24:35 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	g_status = 1;
	data->idx = 0;
	data->path = 0;
	data->env_height = ft_strarr_height(envp);
	data->env = (char **)malloc(sizeof(char *) * (data->env_height + 1));
	data->env[data->env_height] = NULL;
	printf("height=%d\n", data->env_height);
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	data->stdio[0] = dup(STDIN_FILENO);
	data->stdio[1] = dup(STDOUT_FILENO);
	data->pipe_flag = 0;
	data->redirect_flag = 0;
	ft_sort_env(data);
	return ;
}
