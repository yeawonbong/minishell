#include "../minishell.h"

char 	*ft_strjoin_free(char *dest, char *src)
{
	char	*temp;

	temp = dest;
	dest = ft_strjoin(temp, src);
	free(temp);
	return (dest);
}

void	init_re(t_re *re, char **space)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (space[i])
	{
		if (ft_strchr("<>", space[i][0]))
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

char	*join_cmd(char *space, char *cmd_j)
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

void	get_type(t_re *re, char *space, int argc)
{
	if (space[1] == '>')
		re->re_type[argc] = 2;
	else if(space[0] == '>')
		re->re_type[argc] = 1;
	else if (space[0] == '<')
		re->re_type[argc] = 3;
}

void	get_redirect(char *cmds, t_re *re)//t_data *data
{
	char 	**space;
	int	i;

	i = 0;
	space = ft_split(parse_redir(cmds), ' ');
	init_re(re, space);
	while (space[i])
	{
		if (ft_strchr("<>", space[i][0]))
		{
			get_type(re, space[i], re->re_count);
			if (ft_strchr("<>", space[i + 1][0]))
			{
 					//syntax error near unexpected token ' '
			}
			else
				re->re_file[re->re_count++] = ft_strdup(space[++i]);
		}
		else
			re->cmd_j = join_cmd(space[i], re->cmd_j);
		i++;
	}
}
