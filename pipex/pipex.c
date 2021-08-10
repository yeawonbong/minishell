/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:05:36 by sma               #+#    #+#             */
/*   Updated: 2021/07/04 16:35:35 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void			child_p(char **argv, char **envp, t_data *data, int fd[2])
{
	redirect_in(argv[1]);
	pipe_connect(fd, STDOUT_FILENO);
	execve(data->path, data->cmd, envp);
}

void			parent_p(char **argv, char **envp, t_data *data, int fd[2])
{
	run_cmd(argv, envp, data);
	redirect_out(argv[4]);
	wait(0);
	pipe_connect(fd, STDIN_FILENO);
	execve(data->path, data->cmd, envp);
}

void			data_init(t_data *data)
{
	data->count = 2;
	data->path = 0;
	data->cmd = 0;
}

int				check_arg(char **argv)
{
	int			fd;

	fd = open(argv[1], O_RDWR);
	if (fd < 0)
	{
		close(fd);
		perror("cmd error");
		exit(1);
	}
	close(fd);
	return (fd);
}

int				main(int argc, char **argv, char **envp)
{
	pid_t		pid;
	int			fd[2];
	t_data		data;

	data_init(&data);
	check_arg(argv);
	if (argc != 5)
	{
		perror("Error");
		exit(1);
	}
	run_cmd(argv, envp, &data);
	pipe(fd);
	pid = fork();
	if (pid == 0)
		child_p(argv, envp, &data, fd);
	else
		parent_p(argv, envp, &data, fd);
	return (0);
}
