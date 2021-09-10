/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_insert_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:30:24 by ybong             #+#    #+#             */
/*   Updated: 2021/09/10 17:46:17 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	r_utils_init(t_utils *r_u)
{
	r_u->subs = ft_strdup("");
	r_u->join = ft_strdup("");
	r_u->ret = ft_strdup("");
	r_u->len = 0;
	r_u->idx = 0;
}

static	void	ft_retjoin_free(t_utils *r_u, char *str)
{
	char	*temp;

	temp = r_u->ret;
	r_u->ret = ft_strjoin(temp, str);
	free(temp);
}

static	void	insert_space(t_utils *r_u, int flag, char *cmds)
{
	free(r_u->subs);
	r_u->subs = ft_substr(cmds, r_u->idx - r_u->len + flag, r_u->len - flag);
	free(r_u->join);
	if (cmds[r_u->idx] == '>' && cmds[r_u->idx + 1] != '>')
		r_u->join = ft_strjoin(r_u->subs, " > ");
	else if ((cmds[r_u->idx] == '>') && (cmds[r_u->idx + 1] == '>'))
	{
		r_u->join = ft_strjoin(r_u->subs, " >> ");
		r_u->idx++;
	}
	else if (cmds[r_u->idx] == '<' && cmds[r_u->idx + 1] != '<')
		r_u->join = ft_strjoin(r_u->subs, " < ");
	else if (cmds[r_u->idx] == '<' && cmds[r_u->idx + 1] == '<')
	{
		r_u->join = ft_strjoin(r_u->subs, " << ");
		r_u->idx++;
	}
	ft_retjoin_free(r_u, r_u->join);
	r_u->len = 0;
}

char	*parse_redir(char *cmds)
{
	t_utils	r_u;
	int		flag;

	flag = 0;
	r_utils_init(&r_u);
	while (cmds[r_u.idx])
	{
		if (ft_strchr("<>", cmds[r_u.idx]))
		{
			insert_space(&r_u, flag, cmds);
			flag = 1;
		}
		r_u.len++;
		r_u.idx++;
	}
	if (r_u.len > 1)
	{
		free(r_u.subs);
		r_u.subs = ft_substr(cmds, r_u.idx - r_u.len + flag, r_u.len - flag);
		ft_retjoin_free(&r_u, r_u.subs);
	}
	free(r_u.join);
	free(r_u.subs);
	return (r_u.ret);
}
