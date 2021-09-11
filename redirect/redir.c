/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:29 by ybong             #+#    #+#             */
/*   Updated: 2021/09/11 18:07:35 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *dest, char *src)
{
	char	*temp;

	temp = dest;
	dest = ft_strjoin(temp, src);
	free(temp);
	return (dest);
}

static	int	redir_exec(t_re *re)
{
	int		i;
	pid_t	pid;
	int		error;

	i = 0;
	pid = 0;
	while (i < re->re_argc)
	{
		if (re->re_type[i] == 1)
			error = redir_1(re->re_file[i]);
		else if (re->re_type[i] == 2)
			error = redir_2(re->re_file[i]);
		else if (re->re_type[i] == 3)
			error = redir_3(re->re_file[i]);
		else if (re->re_type[i] == 4)
			redir_4(re->re_file[i]);
		if (error == -1)
			return (-1);
		i++;
	}
	return (1);
}

int	redirect(t_data *data, int idx)
{
	t_re	re;

	get_redirect(data->cmds[idx], &re);
	free(data->cmds[idx]);
	data->cmds[idx] = re.cmd_j;
	if (redir_exec(&re) == -1)
		return (-1);
	if (check_builtin(data->cmds[data->idx]))
		ft_builtins(data);
	else
	{
		if (exec_in_child(data) == -1)
			return (-1) ;
	}
	return (0);
}
