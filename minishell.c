/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:10 by ybong             #+#    #+#             */
/*   Updated: 2021/09/20 14:16:11 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(t_data *data)
{
	char	**cmd_args;

	cmd_args = ft_split(data->cmds[data->idx], ' ');
	if (g_status == 127)
	{
		dup2(data->stdio[1], STDOUT_FILENO);
		dup2(data->stdio[0], STDIN_FILENO);
		printf("minish: %s: command not found\n", cmd_args[0]);
		ft_split_free(cmd_args);
		return (-1);
	}
	return (0);
}

static	char	*init_data(t_data *data)
{
	char	*buf;
	char	*prompt;

	prompt = ft_strjoin_free(ft_pwd(), "$ ");
	prompt = ft_join_free_all(ft_strdup("ybong_sma@"), prompt);
	buf = readline(prompt);
	if (buf == 0)
	{
		printf("exit\n");
		exit(0);
	}
	if (*buf)
		add_history(buf);
	free(prompt);
	if (ft_strchr(buf, '$') || ft_strchr(buf, '\'') || ft_strchr(buf, '"'))
	{
		buf = ft_modify_buf(data, buf);
		if (!buf)
			return (NULL);
	}
	data->cmds = ft_split(buf, '|');
	data->idx = 0;
	data->redirect_flag = 0;
	return (buf);
}

int	exec_in_child(t_data *data)
{
	pid_t	pid;
	int		sig_num;

	pid = fork();
	if (pid == 0)
	{
		sig_set(2);
		if_pipe_dup2(data, data->fd[1], STDOUT_FILENO, data->fd[0]);
		get_cmd_path(data);
		if (execve(data->path, data->cmd_args, data->env) == -1)
			printf("minishell : %s\n", strerror(errno));
		exit(1);
	}
	else if (pid == -1)
		exit (1);
	else
	{
		sig_set(1);
		wait(&sig_num);
		sig_set(0);
		if ((WIFSIGNALED(sig_num)))
			return (-1);
	}
	g_status = WEXITSTATUS(sig_num);
	return (ft_error(data));
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
		if (data->redirect_flag)
		{
			if (redirect(data, data->idx) == -1)
				break ;
		}
		else
		{
			if (check_builtin(data->cmds[data->idx]))
				ft_builtins(data);
			else
			{
				if (exec_in_child(data) == -1)
					break ;
			}
		}
		if_pipe_dup2(data, data->fd[0], STDIN_FILENO, data->fd[1]);
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
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	sig_set(0);
	while (1)
	{
		buf = init_data(&data);
		if (buf != NULL)
		{
			exec_cmd(&data);
			dup2(data.stdio[0], STDIN_FILENO);
			dup2(data.stdio[1], STDOUT_FILENO);
			free(buf);
			ft_split_free(data.cmds);
		}
	}
	return (0);
}
