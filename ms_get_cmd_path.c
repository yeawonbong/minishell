/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:11:37 by sma               #+#    #+#             */
/*   Updated: 2021/09/20 15:00:59 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_free(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i++]);
	}
	free(array);
}

static	char	**get_path(char **env)
{
	char	*cmds;
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			cmds = env[i];
			cmds += 5;
			paths = ft_split(cmds, ':');
			return (paths);
		}
		i++;
	}
	return (0);
}

static	char	*path_join(char **paths, char *cmds)
{
	char	*path;
	char	*temp;
	int		i;
	int		fd;

	i = 0;
	while (paths && paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free(temp, cmds);
		fd = open(path, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			return (path);
		}
		free(path);
		close(fd);
		i++;
	}
	exit(127);
	return (0);
}

void	get_cmd_path(t_data *data)
{
	char	**paths;

	paths = get_path(data->env);
	data->cmd_args = ft_split(data->cmds[data->idx], ' ');
	if (data->cmd_args[0][0] == '.' || data->cmd_args[0][0] == '/')
	{
		split_free(paths);
		data->path = data->cmd_args[0];
		return ;
	}
	data->path = path_join(paths, data->cmd_args[0]);
	if (data->path != 0)
	{
		split_free(paths);
		return ;
	}
	split_free(data->cmds);
	split_free(paths);
}
