/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 13:25:17 by sma               #+#    #+#             */
/*   Updated: 2021/09/27 16:12:23 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
				break ;
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

	u.unset_arg = data->cmd_args;
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
}
