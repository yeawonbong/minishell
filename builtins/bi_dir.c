/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:42 by ybong             #+#    #+#             */
/*   Updated: 2021/09/10 18:43:20 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_pwd(void)
{
	char	buf[BUFSIZE];
	char	*ptr;

	getcwd(buf, BUFSIZE);
	ptr = buf;
	return (ptr);
}

void	ft_echo(char *cmd)
{
	char	**echo_arg;
	int		i;

	echo_arg = ft_split(cmd, ' ');
	i = 1;
	if (echo_arg[1])
	{
		while (echo_arg[i])
		{
			printf("%s", echo_arg[i]);
			if (echo_arg[i + 1])
				printf(" ");
			i++;
		}
	}
	printf("\n");
	ft_split_free(echo_arg);
}