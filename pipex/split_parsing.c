/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:11:37 by sma               #+#    #+#             */
/*   Updated: 2021/07/04 16:35:32 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void			split_free(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i++]);
	}
	free(array);
}

char			**get_path(char **envp)
{
	char		*cmd;
	char		**envir;
	int			i;

	i = 0;
	while (envp[i++])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			cmd = envp[i];
			cmd += 5;
			envir = ft_split(cmd, ':');
			return (envir);
		}
	}
	return (0);
}

char			*path_join(char **envir, char *cmd)
{
	char		*p;
	char		*temp;
	int			i;
	int			fd;

	i = 0;
	while (envir[i])
	{
		temp = ft_strjoin(envir[i], "/");
		p = ft_strjoin(temp, cmd);
		fd = open(p, O_RDONLY);
		if (fd > 0)
		{
			free(temp);
			return (p);
		}
		free(temp);
		free(p);
		close(fd);
		i++;
	}
	write(1, "cmd error\n", 10);
	exit(1);
	return (0);
}

void			run_cmd(char **argv, char **envp, t_data *data)
{
	char		**envir;

	envir = get_path(envp);
	if (data->path != 0)
		free(data->path);
	if (data->cmd != 0)
		split_free(data->cmd);
	while (data->count < 4)
	{
		data->cmd = ft_split(argv[data->count], ' ');
		data->path = path_join(envir, data->cmd[0]);
		if (data->path > 0)
		{
			data->count++;
			break ;
		}
		split_free(data->cmd);
		data->count++;
	}
	split_free(envir);
}
