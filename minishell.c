/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:10 by ybong             #+#    #+#             */
/*   Updated: 2021/09/10 18:25:04 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*init_data(t_data *data)
{
	char	*buf;

	printf("ybong_sma@%s", ft_pwd());
	buf = readline("$ ");
	if (*buf)
		add_history(buf);
	if (ft_strchr(buf, '$') && *buf) //+ "" ''
		buf = ft_modify_buf(data, buf);
	data->cmds = ft_split(buf, '|');
	data->idx = 0;
	data->redirect_flag = 0;
	return (buf);
}

static	void	exec_in_child(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (data->redirect_flag)
			redirect(data, data->idx);
		if (data->cmds[data->idx + 1] != NULL)
		{
			dup2(data->fd[1], STDOUT_FILENO);
			close(data->fd[0]);
		}
		get_cmd_path(data);
		if (execve(data->path, data->cmd_args, data->env) == -1)
			perror("execve error :");
	}
	else
		wait(0);
}

static	void	exec_cmd(t_data *data)
{
	while (data->cmds[data->idx])
	{
		pipe(data->fd);
		data->redirect_flag = 0;
		if (ft_strchr(data->cmds[data->idx], '<') || \
						ft_strchr(data->cmds[data->idx], '>'))
			data->redirect_flag = 1;
		if (check_builtin(data->cmds[data->idx]))
			ft_builtins(data);
		else
			exec_in_child(data);
		if (data->cmds[data->idx + 1] != NULL)
		{
			dup2(data->fd[0], STDIN_FILENO);
			close(data->fd[1]);
		}
		free(data->cmds[data->idx]);
		data->idx++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*buf;

	if (1 < argc || argv[1])
		return (0);
	buf = NULL;
	ft_filldata(&data, envp);
	while (1)
	{
		buf = init_data(&data);
		exec_cmd(&data);
		dup2(data.stdio[1], STDOUT_FILENO);
		dup2(data.stdio[0], STDIN_FILENO);
		free(buf);
		free(data.cmds);
	}
	return (0);
}
