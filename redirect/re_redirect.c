/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:27 by ybong             #+#    #+#             */
/*   Updated: 2021/09/20 13:16:28 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_1(char *file)
{
	int		fd;
	// pid_t	pid;
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
	pid_t	pid;
	char	*buf;
	int		fd;
	int		sig_num;

	buf = NULL;
	fd = dup(STDOUT_FILENO);
	pipe(re_fd);
	pid = fork();
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
	dup2(re_fd[0], STDIN_FILENO);
	close(re_fd[1]);
	close(re_fd[0]);
	return (0);
}
