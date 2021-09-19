/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_modify_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:28:47 by ybong             #+#    #+#             */
/*   Updated: 2021/09/19 23:46:08 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_quote_process(t_data *data, t_qte *qte, char *buf, t_var var)
{
	int	i;

	if (*qte->newbuf)
	{
		i = 1;
		while (qte->newbuf[i] != *qte->newbuf)
			i++;
	}
	qte->inqte = ft_substr(qte->newbuf, 1, i - 1);
	if (*qte->newbuf == '"' || !*qte->newbuf)
		qte->modified = ft_join_free_all(qte->modified, \
								ft_modify_envar(data, &var, qte->inqte));
	else if (*qte->newbuf == '\'')
		qte->modified = ft_join_free_all(qte->modified, qte->inqte);
	qte->newbuf += i + 1;
}

static void	ft_modify_quote(t_data *data, t_qte *qte, char *buf)
{
	t_var	var;
	int		i;

	i = 0;
	qte->modified = ft_strdup("");
	qte->newbuf = buf;
	while (*qte->newbuf)
	{
		i = 0;
		while ((qte->newbuf[i]) && qte->newbuf[i] != '\'' \
										&& qte->newbuf[i] != '"')
			i++;
		qte->modified = ft_join_free_all(qte->modified, \
										ft_substr(qte->newbuf, 0, i));
		qte->newbuf = qte->newbuf + i;
		if (qte->newbuf && (!ft_strchr(qte->newbuf + 1, (int)*qte->newbuf)))
		{
			printf("syntax error unclosed quote\n"); // 에러처리 생각
			exit(0);
		}
		else
			ft_quote_process(data, qte, buf, var);
	}
}

char	*ft_modify_buf(t_data *data, char *buf)
{
	t_var	var;
	t_qte	qte;

	if (!ft_strchr(buf, '\'') && !ft_strchr(buf, '"')) //noquote
	{
		ft_modify_envar(data, &var, buf);
		free(buf);
		return (var.modified);
	}
	else
		ft_modify_quote(data, &qte, buf);
	free(buf);
	return (qte.modified);
}
