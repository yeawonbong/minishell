/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:11:37 by sma               #+#    #+#             */
/*   Updated: 2021/09/04 16:56:29 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char		*cmds;
	char		**paths;
	int			i;

	i = 0;
	while (envp[i++])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			cmds = envp[i];
			cmds += 5;
			paths = ft_split(cmds, ':');
			return (paths);
		}
	}
	return (0);
}

char			*path_join(char **paths, char *cmds)
{
	char		*path;
	char		*temp;
	int			i;
	int			fd;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmds);
		fd = open(path, O_RDONLY);
		if (fd > 0)
		{
			free(temp);
			return (path);
		}
		free(temp);
		free(path);
		close(fd);
		i++;
	}
	write(1, "cmds error in path join\n", 24);
	exit(1);
	return (0);
}

// ls | grep 

void			run_cmd(char **envp, t_data *data)
{
	char		**paths;
	
	paths = get_path(envp);
	// ft_split_args //while tokenization, pars "", ''
	data->cmd_args = ft_split(data->cmds[data->idx], ' '); // 토큰화
	// printf("cmds = %s, idx = %d\n", data->cmds[data->idx], data->idx);
	data->path = path_join(paths, data->cmd_args[0]); // ((ls,  -l, NULL),   grep "hello", NULL)
	if (data->path != 0)
	{
		split_free(paths);
		return ;
	}
	split_free(data->cmds);
	split_free(paths);
}
