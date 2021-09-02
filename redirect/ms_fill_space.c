#include "../minishell.h"

void	r_utils_init(t_utils *r_u)
{
	r_u->subs = ft_strdup("");
	r_u->join = ft_strdup("");
	r_u->ret = ft_strdup("");
	r_u->len = 0;
	r_u->idx = 0;
}

void	ft_retjoin_free(t_utils *r_u, char *str)
{
	char	*temp;

	temp = r_u->ret;
	r_u->ret = ft_strjoin(temp, str);
	free(temp);
}

void	get_parse(t_utils *r_u, int flag, char *cmds)
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
	else if (cmds[r_u->idx] == '<')
		r_u->join = ft_strjoin(r_u->subs, " < ");
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
			get_parse(&r_u, flag, cmds);
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

// int main(void)
// {
//     char *str = ">< >cat>hi>>>>hi>dydy nlnl< > >>";
//     char *s;

//     s = parse_redir(str);
//     printf("%s|\n", s);
//     while (1)
//     {

//     }
//     return (0);
// }