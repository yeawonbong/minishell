#include "../minishell.h"

char	*ft_strjoin_free(char *dest, char *src)
{
	char	*temp;

	temp = dest;
	dest = ft_strjoin(temp, src);
	free(temp);
	return (dest);
}

int	redir_exec(t_re *re)
{
	int		i;

	i = 0;
	while (i < re->re_argc)
	{
		if (re->re_type[i] == 1)
			redir_1(re->re_file[i]);
		else if (re->re_type[i] == 2)
			redir_2(re->re_file[i]);
		else if (re->re_type[i] == 3)
			redir_3(re->re_file[i]);
		else if (re->re_type[i] == 4)
			redir_4(re->re_file[i]);
		i++;
	}
	return (1);
}

void	redirect(t_data *data, int idx)
{
	t_re	re;

	get_redirect(data->cmds[idx], &re);
	free(data->cmds[idx]);
	data->cmds[idx] = re.cmd_j;
	redir_exec(&re);
}
