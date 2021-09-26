/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:15:28 by sma               #+#    #+#             */
/*   Updated: 2021/09/26 17:08:14 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_cmds(t_data *data, int idx)
{
	char	*str;
	int		i;

	i = 1;
	str = ft_strdup(data->cmd_args[0]);
	while (data->cmd_args[i])
	{
		str = ft_strjoin_free(str, " ");
		str = ft_strjoin_free(str, data->cmd_args[i++]);
	}
	ft_split_free(data->cmd_args);
	free(data->cmds[idx]);
	data->cmds[idx] = str;
}

int	re_exec_err(t_re *re)
{
	ft_split_free(re->re_file);
	free(re->re_type);
	return (-1);
}

void	close_dup_fd(int re_fd[2])
{
	dup2(re_fd[0], STDIN_FILENO);
	close(re_fd[1]);
	close(re_fd[0]);
}

int	child_in_buf(int re_fd[2], char *buf, int fd, char *str)
{
	pid_t	pid;
	int		sig_num;

	pid = fork();
	sig_num = 0;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		get_buf(re_fd, buf, fd, str);
	}
	else
	{
		signal(SIGINT, redirect_handler);
		wait(&sig_num);
		sig_set(0);
		if (WIFSIGNALED(sig_num) && WTERMSIG(sig_num) == 2)
			return (-1);
		g_status = WEXITSTATUS(sig_num);
	}
	return (0);
}
