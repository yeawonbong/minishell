/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_in_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:42 by ybong             #+#    #+#             */
/*   Updated: 2021/09/17 18:28:24 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd(void)
{
	return (getcwd(NULL, 0));
}

void	ft_echo(char *cmd)
{
	char	**echo_arg;
	int		i;

	echo_arg = ft_split(cmd, ' ');
	i = 1;
	if (echo_arg[1])
	{
		if (!ft_strncmp(echo_arg[i], "-n", ft_strlen(echo_arg[i])))
			i++;
		while (echo_arg[i])
		{
			printf("%s", echo_arg[i]);
			if (echo_arg[i + 1])
				printf(" ");
			i++;
		}
	}
	if (ft_strncmp(echo_arg[1], "-n", ft_strlen(echo_arg[1])))
		printf("\n");
	ft_split_free(echo_arg);
}
