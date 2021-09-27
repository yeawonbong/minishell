/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_in_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:47 by ybong             #+#    #+#             */
/*   Updated: 2021/09/27 16:12:23 by ybong            ###   ########.fr       */
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

void	replace_process(t_data *data, t_unset *u)
{
	u->t = 0;
	while (data->cmd_args[u->u][u->t] != '=')
		u->t++;
	u->var2 = ft_substr(data->cmd_args[u->u], 0, u->t);
	if (!ft_strncmp(u->var, u->var2, longer_len(u->var, u->var2)))
	{
		free(data->env[u->i]);
		data->env[u->i] = data->cmd_args[u->u];
		data->cmd_args[u->u] = ft_strdup("");
	}
	free(u->var2);
}

void	ft_export_replace(t_data *data)
{
	t_unset	u;

	u.i = 0;
	while (data->env[u.i])
	{
		u.j = 0;
		while (data->env[u.i][u.j] != '=')
			u.j++;
		u.var = ft_substr(data->env[u.i], 0, u.j);
		u.u = 1;
		while (data->cmd_args[u.u])
		{
			if (ft_strchr(data->cmd_args[u.u], '='))
				replace_process(data, &u);
			u.u++;
		}
		free(u.var);
		u.i++;
	}
}

void	ft_export(t_data *data, int child)
{
	char	**exp_arg;
	char	**tempenv;
	int		add;
	int		i;

	tempenv = NULL;
	ft_export_replace(data);
	exp_arg = data->cmd_args;
	add = 0;
	i = 0;
	while (exp_arg[i])
	{
		if (*exp_arg[i] && ft_strchr(exp_arg[i], '='))
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
}

void	ft_cd(t_data *data)
{
	char	**cd_args;
	int		i;
	char	*path;

	i = 0;
	cd_args = data->cmd_args;
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
