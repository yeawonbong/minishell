/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:15:28 by sma               #+#    #+#             */
/*   Updated: 2021/09/24 15:39:50 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
