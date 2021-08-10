/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:38:31 by sma               #+#    #+#             */
/*   Updated: 2021/07/04 16:35:34 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int			redirect_in(char *file)
{
	int		fd;

	fd = open(file, O_RDWR);
	if (fd < 0)
	{
		close(fd);
		perror("open error");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int			redirect_out(char *file)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		close(fd);
		perror("open error");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

void		pipe_connect(int fd[2], int f)
{
	dup2(fd[f], f);
	close(fd[0]);
	close(fd[1]);
}
