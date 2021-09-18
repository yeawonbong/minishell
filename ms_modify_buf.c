/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_modify_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:28:47 by ybong             #+#    #+#             */
/*   Updated: 2021/09/18 17:33:19 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_quote_process(t_data *data, t_qte *qte, char *buf)
// {
// 	int	i;
// 	while (*qte->newbuf)
// 	{
		
// 	}

// }


static void	ft_modify_quote(t_data *data, t_qte *qte, char *buf)
{
	t_var	var;
	int	i;
	
	i = 0;
	qte->modified = ft_strdup("");
	qte->newbuf = buf;

	while (*qte->newbuf)
	{
		i = 0;
		printf("뉴버프: %s\n", qte->newbuf);
		while ((qte->newbuf[i]) && qte->newbuf[i] != '\'' && qte->newbuf[i] != '"')
			i++;
		printf("뽑아보자인덱스: %d\n", i );
		qte->modified = ft_join_free_all(qte->modified, ft_substr(qte->newbuf, 0, i));
		printf("init modified=%s, %d\n", qte->modified, i);
		if (qte->newbuf[i] && (!ft_strchr(&qte->newbuf[i + 1], (int)qte->newbuf[i])))
		{
			printf("error: unclosed quote\n"); // 에러처리 생각
			exit(0);
		}
		else
		{
			if (qte->newbuf[i])
			{
				qte->qidx = i++;
				while (qte->newbuf[i] == qte->newbuf[qte->qidx])
					i++;
			}
			qte->newbuf += i;
			qte->inqte = ft_substr(qte->newbuf, qte->qidx, i - qte->qidx - 1); //free
			if (*qte->newbuf == '"' || !*qte->newbuf)
				qte->modified = ft_join_free_all(qte->modified, ft_modify_envar(data, &var, qte->inqte));
			else if (*qte->newbuf == '\'')
				qte->modified = ft_join_free_all(qte->modified, qte->inqte);
//!!!!!!!!!			// if (*qte->newbuf)
			// 	qte->newbuf += i + 1; //inquote 개수만큼 더해줘야함
		}
	}
}

char	*ft_modify_buf(t_data *data, char *buf)
{
	t_var	var;
	t_qte	qte;

printf("init buf=%s\n", buf);
	if (!ft_strchr(buf, '\'') && !ft_strchr(buf, '"'))// quote가 없는 경우
	{
		printf("NO quote\n");
		ft_modify_envar(data, &var, buf);
		free(buf);
		return (var.modified);
	}
	else
		ft_modify_quote(data, &qte, buf);
	free(buf);
	return (qte.modified);
}
// echo sfd's$USER' asdsd$PATH