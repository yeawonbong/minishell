/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_modify_envar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 23:47:56 by ybong             #+#    #+#             */
/*   Updated: 2021/09/19 23:47:58 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_var(t_data *data, char *var)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] != '=')
			j++;
		if (!ft_strncmp(data->env[i], var, j) \
		&& !ft_strncmp(data->env[i], var, ft_strlen(var)))
			break ;
		i++;
	}
	free(var);
	if (data->env[i])
		return (ft_strdup(data->env[i] + j + 1));
	else
		return (ft_strdup(""));
}

void	ft_envar_process(t_data *data, t_var *var)
{
	if (*var->newbuf == '$')
	{
		var->var = ft_strdup("$$");
		var->newbuf++;
	}
	else if (*var->newbuf == '?')
	{
		var->var = ft_itoa(g_status);
		var->newbuf++;
	}
	else
	{
		var->i = 0;
		while (ft_isdigit(*(var->newbuf + var->i)) \
		|| ft_isalpha(*(var->newbuf + var->i)))
			var->i++;
		if (var->i == 0)
			var->var = ft_strdup("$");
		else
		{
			var->var = ft_substr(var->newbuf, 0, var->i);
			var->var = ft_replace_var(data, var->var);
			var->newbuf += var->i;
		}
	}
}

char	*ft_modify_envar(t_data *data, t_var *var, char *buf)
{
	var->modified = ft_strdup("");
	var->newbuf = buf;
	while (ft_strchr(var->newbuf, '$'))
	{
		var->i = 0;
		while (*(var->newbuf + var->i) != '$')
			var->i++;
		var->modified = ft_join_free_all(var->modified, \
							ft_substr(var->newbuf, 0, var->i));
		var->newbuf += var->i + 1;
		ft_envar_process(data, var);
		var->modified = ft_join_free_all(var->modified, var->var);
	}
	var->newbuf = ft_strdup(var->newbuf);
	var->modified = ft_join_free_all(var->modified, var->newbuf);
	return (var->modified);
}
