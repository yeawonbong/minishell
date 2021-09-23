/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:27 by ybong             #+#    #+#             */
/*   Updated: 2021/09/20 20:01:54 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_1(char *file)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("error : %s\n", strerror(errno));
		g_status = 1;
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redir_2(char *file)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("error : %s\n", strerror(errno));
		g_status = 1;
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redir_3(char *file)
{
	int		fd;

	fd = open(file, O_RDWR, 0644);
	if (fd < 0)
	{
		printf("error : %s\n", strerror(errno));
		g_status = 1;
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

void	get_buf(int re_fd[2], char *buf, int fd, char *str)
{
	while (1)
	{
		buf = readline("> ");
		if (buf == 0)
		{
			exit(0);
		}
		if (ft_strlen(buf) == ft_strlen(str))
		{
			if (ft_strncmp(buf, str, ft_strlen(str)) == 0)
			{	
				free(buf);
				close(re_fd[1]);
				exit(0);
			}
		}
		dup2(re_fd[1], STDOUT_FILENO);
		close(re_fd[0]);
		printf("%s\n", buf);
		free(buf);
		dup2(fd, STDOUT_FILENO);
	}
}

int	redir_4(char *str)
{
	int		re_fd[2];
	char	*buf;
	int		fd;

	buf = NULL;
	fd = dup(STDOUT_FILENO);
	pipe(re_fd);
	if (child_in_buf(re_fd, buf, fd, str) == -1)
		return (-1);
	close_dup_fd(re_fd);
	return (0);
}
