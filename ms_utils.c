/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:40:36 by ybong             #+#    #+#             */
/*   Updated: 2021/09/10 17:40:38 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_free(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i])
		free(strarr[i++]);
	free(strarr);
}

int	longer_len(char *str, char *str2)
{
	int	s;
	int	s2;

	s = ft_strlen(str);
	s2 = ft_strlen(str2);
	if (s > s2)
		return (s);
	else
		return (s2);
}

int	ft_strarr_height(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
