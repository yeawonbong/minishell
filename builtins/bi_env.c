/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:45 by ybong             #+#    #+#             */
/*   Updated: 2021/09/10 17:51:14 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i++]);
	}
}

void	ft_copy_env(char **src, char **dest)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	return ;
}

void	ft_sort_env(t_data *data)
{
	int	temp;
	int	i;
	int	j;

	i = -1;
	data->sort_env = (int *)malloc(sizeof(int) * data->env_height);
	while (++i < data->env_height)
		data->sort_env[i] = i;
	j = 0;
	while (0 < data->env_height - j)
	{
		i = 0;
		while (i + 1 < data->env_height)
		{
			if (0 < ft_strncmp(data->env[data->sort_env[i]], data->env[data->\
			sort_env[i + 1]], longer_len(data->env[i], data->env[i + 1])))
			{
				temp = data->sort_env[i];
				data->sort_env[i] = data->sort_env[i + 1];
				data->sort_env[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
}
