/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:58:14 by ybong             #+#    #+#             */
/*   Updated: 2021/09/17 18:31:46 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(char *buf)
{
	if ((!(ft_strncmp(buf, "exit", 4)) && (!*(buf + 4) || *(buf + 4) == ' ')) \
	|| (!(ft_strncmp(buf, "export", 6)) && (!*(buf + 6) || *(buf + 6) == ' ')) \
	|| (!(ft_strncmp(buf, "unset", 5)) && (!*(buf + 5) || *(buf + 5) == ' ')) \
	|| (!(ft_strncmp(buf, "env", 3)) && (!*(buf + 3) || *(buf + 3) == ' ' )) \
	|| (!(ft_strncmp(buf, "cd", 2)) && (!*(buf + 2) || *(buf + 2) == ' ')) \
	|| (!(ft_strncmp(buf, "pwd", 3)) && (!*(buf + 3) || *(buf + 3) == ' ')) \
	|| (!(ft_strncmp(buf, "echo", 4)) && (!*(buf + 4) || *(buf + 4) == ' ')))
		return (1);
	return (0);
}

static	void	ft_builtins_in_child(t_data *data, char *cmd)
{
	if (data->cmds[data->idx + 1] != NULL)
	{
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[0]);
	}
	if (!(ft_strncmp(cmd, "export", 6)) && (!*(cmd + 6)))
	{
		ft_export(data, 1);
	}
	else if (!(ft_strncmp(cmd, "env", 3)) \
			&& (!*(cmd + 3) || *(cmd + 3) == ' '))
		ft_env(data);
	else if (!(ft_strncmp(cmd, "pwd", 3)) \
			&& (!*(cmd + 3) || *(cmd + 3) == ' '))
		printf("%s\n", ft_pwd());
	else if (!(ft_strncmp(cmd, "echo", 4)) \
			&& (!*(cmd + 4) || *(cmd + 4) == ' '))
		ft_echo(cmd);
	exit(0);
}

static	int	ft_builtins_in_parents(t_data *data, char *cmd)
{
	if (!(ft_strncmp(cmd, "export", 6)) && (*(cmd + 6) || *(cmd + 6) == ' '))
	{
		ft_export(data, 0);
		return (0);
	}
	else if (!(ft_strncmp(cmd, "unset", 5)) && \
					(!*(cmd + 5) || *(cmd + 5) == ' ' ))
	{
		ft_unset(data);
		return (0);
	}
	else if (!(ft_strncmp(cmd, "cd", 2)) && (!*(cmd + 2) || *(cmd + 2) == ' '))
	{
		ft_cd(data);
		return (0);
	}
	return (-1);
}

void	ft_builtins(t_data *data)
{
	pid_t	pid;
	int		i;
	char	*cmd;

	i = data->idx;
	// redirect(data, data->idx);
	cmd = ft_strtrim(data->cmds[i], " ");
	if (!(ft_strncmp(cmd, "exit", 4)) && (!*(cmd + 4) || *(cmd + 4) == ' '))
	{
		printf("exit\n");
		exit(0);
	}
	if (!ft_builtins_in_parents(data, cmd))
	{
		g_status = 0;
		free(cmd);
		return ;
	}
	pid = fork();
	if (pid == 0)
		ft_builtins_in_child(data, cmd);
	else
		wait(&g_status);
	free(cmd);
}
