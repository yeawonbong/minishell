/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 20:19:19 by sma               #+#    #+#             */
/*   Updated: 2021/09/27 16:12:25 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_arg(t_data *data)
{
	int	i;

	i = 0;
	if (!data->cmd_args[1])
		exit(g_status);
	while (data->cmd_args[1][i])
	{
		if (i == 0 && data->cmd_args[1][0] == '-')
			i++;
		if (!ft_isdigit(data->cmd_args[1][i]))
		{
			printf("minish: exit: %s: numeric argument required\n", \
													data->cmd_args[1]);
			exit(255);
		}
		i++;
	}
	exit(ft_atoi(data->cmd_args[1]));
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_args[i])
		i++;
	if (i < 3)
		ft_exit_arg(data);
	printf("minish: exit: too many argumets\n");
	g_status = 1;
}

void	cd_err(char **cd_args)
{
	if (chdir(cd_args[1]) == -1)
	{
		printf("minish : cd: no such file or directory: %s\n", cd_args[1]);
		g_status = 1;
		return ;
	}
	g_status = 0;
}
