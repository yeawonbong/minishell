/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_get_re.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:21 by ybong             #+#    #+#             */
/*   Updated: 2021/09/20 14:59:07 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	init_re(t_re *re, char *cmds)
{
	int		i;
	int		count;

	re->space = ft_split(re->parse = parse_redir(cmds), ' ');
	i = 0;
	count = 0;
	while (re->space[i])
	{
		if (ft_strchr("<>", re->space[i][0]))
			count++;
		i++;
	}
	re->re_argc = count;
	if (count > 0)
		re->re_type = (int *)malloc(sizeof(int) * count);
	re->re_file = (char **)malloc(sizeof(char *) * (count + 1));
	re->re_file[count] = NULL;
	re->cmd_j = 0;
	re->re_count = 0;
}

static	char	*join_cmd(char *space, char *cmd_j)
{
	if (cmd_j == 0)
		cmd_j = ft_strdup(space);
	else
	{	
		cmd_j = ft_strjoin_free(cmd_j, " ");
		cmd_j = ft_strjoin_free(cmd_j, space);
	}
	return (cmd_j);
}

static	void	get_type(t_re *re, char *space, int argc)
{
	if (space[0] == '>' && space[1] != '>')
		re->re_type[argc] = 1;
	else if (space[0] == '>' && space[1] == '>')
		re->re_type[argc] = 2;
	else if (space[0] == '<' && space[1] != '<')
		re->re_type[argc] = 3;
	else if (space[0] == '<' && space[1] == '<')
		re->re_type[argc] = 4;
}

static	void	redirect_error(char *str)
{
	if (str == NULL)
	{
		printf("syntax error near unexpected token '%s'\n", "newline");
	}
	else
	{
		printf("syntax error near unexpected token '%s'\n", str);
	}
}

int	get_redirect(char *cmds, t_re *re)
{
	int		i;

	i = 0;
	init_re(re, cmds);
	while (re->space[i])
	{
		if (ft_strchr("<>", re->space[i][0]))
		{
			get_type(re, re->space[i], re->re_count);
			if (re->space[i + 1] == NULL || \
						ft_strchr("<>", re->space[i + 1][0]))
			{
				redirect_error(re->space[i + 1]);
				return (-1);
			}
			else
				re->re_file[re->re_count++] = ft_strdup(re->space[++i]);
		}
		else
			re->cmd_j = join_cmd(re->space[i], re->cmd_j);
		i++;
	}
	free(re->parse);
	ft_split_free(re->space);
	return (0);
}
