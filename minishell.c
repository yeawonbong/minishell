/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:10 by ybong             #+#    #+#             */
/*   Updated: 2021/09/25 17:03:23 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_error(t_data *data)
{
	char	**cmd_args;

	cmd_args = ft_split(data->cmds[data->idx], ' ');
	if (g_status == 127)
	{
		dup2(data->stdio[1], STDOUT_FILENO);
		dup2(data->stdio[0], STDIN_FILENO);
		if (ft_strchr(cmd_args[0], '/'))
			printf("minish: %s: No such file or directory\n", cmd_args[0]);
		else
			printf("minish: %s: command not found\n", cmd_args[0]);
		ft_split_free(cmd_args);
		return (-1);
	}
	ft_split_free(cmd_args);
	return (0);
}

static char	*init_data(t_data *data)
{
	char	*buf;
	char	*prompt;
	char	*temp;
	
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
	data->redirect_flag = 0;
	data->cmds = ft_split("", ' ');
	temp = buf;
	buf = ft_strtrim(temp, "\t ");
	free(temp);
	data->cmds = ft_split_with('|', buf, data->cmds, data);
	printf("%s|\n", data->cmds[1]);
	if (data->cmds == 0)
	{
		data->cmds = ft_split("", ' ');
		free(buf);
		return (ft_strdup(""));
	}
	data->idx = 0;
	return (buf);
}

int	exec_in_child(t_data *data)
{
	pid_t	pid;
	int		sig_num;

	pid = fork();
	if (pid == 0)
		child_exec(data);
	else if (pid == -1)
		exit (1);
	else
	{
		dup2(data->stdio[1], STDOUT_FILENO);
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
		if (check_redir(data->cmds[data->idx]))
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
		if (buf && *buf != 0)
		{
			exec_cmd(&data);
			dup2(data.stdio[0], STDIN_FILENO);
			dup2(data.stdio[1], STDOUT_FILENO);
			// ft_split_free(data.cmds);
		}
		ft_split_free(data.cmds);
		free(buf);
	}
	return (0);
}
