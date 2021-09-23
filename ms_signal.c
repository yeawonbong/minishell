/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:34:48 by ybong             #+#    #+#             */
/*   Updated: 2021/09/20 19:38:37 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_set(int i)
{
	if (i == 0)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == 1)
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
	}
	else if (i == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("%c[K\n", 27);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_status = 130;
	}
}

void	child_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("%c[K\n", 27);
		g_status = 130;
	}
	if (signo == SIGQUIT)
	{
		printf("Quit: 3\n");
		g_status = 131;
	}
}

void	redirect_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("%c[K\n", 27);
		printf("\n");
		g_status = 130;
	}
}
