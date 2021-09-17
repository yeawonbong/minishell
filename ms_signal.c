/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:34:48 by ybong             #+#    #+#             */
/*   Updated: 2021/09/17 18:41:02 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void sigint_handler(int signo)
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

void child_handler(int signo)
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

void redirect_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("%c[K\n", 27);
        // printf("\n");
		g_status = 130;
	}
	signal(SIGINT, sigint_handler);
}
