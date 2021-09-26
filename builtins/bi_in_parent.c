/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_in_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:47 by ybong             #+#    #+#             */
/*   Updated: 2021/09/26 17:54:52 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_add(t_data *data, char **exp_arg, char **tempenv, int add)
{
	int	i;

	tempenv = (char **)malloc(sizeof(char *) * (data->env_height + add + 1));
	ft_copy_env(data->env, tempenv);
	i = 1;
	while (exp_arg[i])
	{
		if (*exp_arg[i] == '=')
		{
			printf("minishell: bad assignment\n");
			ft_split_free(tempenv);
			return ;
		}
		else if (ft_strchr(exp_arg[i], '='))
		{
			tempenv[data->env_height] = ft_strdup(exp_arg[i]);
			data->env_height++;
		}
		i++;
	}
	tempenv[data->env_height] = NULL;
	ft_split_free(data->env);
	data->env = tempenv;
	free(data->sort_env);
	ft_sort_env(data);
}

void	ft_export(t_data *data, int child)
{
	char	**exp_arg;
	char	**tempenv;
	int		add;
	int		i;

	tempenv = NULL;
	exp_arg = ft_split(data->cmds[data->idx], ' ');
	add = 0;
	i = 0;
	while (exp_arg[i])
	{
		if (ft_strchr(exp_arg[i], '='))
			add++;
		i++;
	}
	if (i == 1 && child)
	{
		i = 0;
		while (data->env[i])
			printf("declare -x %s\n", data->env[data->sort_env[i++]]);
	}
	else
		ft_export_add(data, exp_arg, tempenv, add);
	ft_split_free(exp_arg);
}

static void	cd_err(char **cd_args)
{
	if (chdir(cd_args[1]) == -1)
	{
		printf("minish : cd: no such file or directory: %s\n", cd_args[1]);
		g_status = 1;
		ft_split_free(cd_args);
		return ;
	}
	ft_split_free(cd_args);
	g_status = 0;
}

void	ft_cd(t_data *data)
{
	char	**cd_args;
	int		i;
	char	*path;

	i = 0;
	cd_args = ft_split(data->cmds[data->idx], ' ');
	if (cd_args[1] == NULL)
	{
		while (data->env[i])
		{
			if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
			{
				path = data->env[i] + 5;
				break ;
			}
			i++;
		}
		chdir(path);
		return ;
	}
	cd_err(cd_args);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (!data->cmd_args[1])
		exit(0);
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
