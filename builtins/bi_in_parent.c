/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_in_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:47 by ybong             #+#    #+#             */
/*   Updated: 2021/09/20 19:27:59 by sma              ###   ########.fr       */
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
			printf("%s\n", data->env[data->sort_env[i++]]);
	}
	else
		ft_export_add(data, exp_arg, tempenv, add);
	ft_split_free(exp_arg);
}

static	void	ft_unset_process(t_data *data, t_unset *u)
{
	while (data->env[u->i])
	{
		u->j = 0;
		while (data->env[u->i][u->j] != '=')
			u->j++;
		u->var = ft_substr(data->env[u->i], 0, u->j);
		u->u = 1;
		while (u->unset_arg[u->u])
		{
			if (!ft_strncmp(u->var, u->unset_arg[u->u], \
					longer_len(u->var, u->unset_arg[u->u])))
				break ;
			u->u++;
		}
		if (!u->unset_arg[u->u])
			u->tempenv[u->t++] = ft_strdup(data->env[u->i]);
		u->i++;
		free(u->var);
	}
	ft_split_free(data->env);
	data->env = u->tempenv;
	free(data->sort_env);
	ft_sort_env(data);
}

static int	ft_unset_valid(t_data *data, char **unset_arg)
{
	t_unset	u;
	int		count;

	u.i = 0;
	u.u = 0;
	count = 0;
	while (data->env[u.i])
	{
		u.j = 0;
		while (data->env[u.i][u.j] != '=')
			u.j++;
		u.var = ft_substr(data->env[u.i], 0, u.j);
		u.u = 1;
		while (unset_arg[u.u])
		{
			if (!ft_strncmp(u.var, unset_arg[u.u], \
					longer_len(u.var, unset_arg[u.u])))
			{
				break ;
			}
			u.u++;
		}
		if (unset_arg[u.u])
			count++;
		free(u.var);
		u.i++;
	}
	return (count);
}

void	ft_unset(t_data *data)
{
	t_unset	u;

	u.unset_arg = ft_split(data->cmds[data->idx], ' ');
	u.tempenv = NULL;
	u.i = 0;
	u.t = 0;
	while (u.unset_arg[u.i])
		u.i++;
	if (u.i == 1)
		ft_putstr_fd("unset: not enough arguments\n", STDOUT_FILENO);
	else
	{
		data->env_height -= ft_unset_valid(data, u.unset_arg);
		u.tempenv = (char **)malloc(sizeof(char *) * (data->env_height + 1));
		u.tempenv[data->env_height] = NULL;
		u.i = 0;
		ft_unset_process(data, &u);
	}
	ft_split_free(u.unset_arg);
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
	chdir(cd_args[1]);
	ft_split_free(cd_args);
}
