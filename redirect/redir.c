#include "../minishell.h"

void	redir_1(char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("error : ");
		exit(1);
		//no such file or directory
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_2(char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("error : ");
		exit(1);
		//no such file or directory
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_3(char *file)
{
	int fd;

	fd = open(file, O_RDWR, 0644);
	if (fd < 0)
	{
		perror("error : ");
		exit(1);
		//no such file or directory
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int     redir_exec(t_re *re)
{
	int	i;

	i = 0;
	while (i < re->re_argc)
	{
		if (re->re_type[i] == 1)
			redir_1(re->re_file[i]);
		else if(re->re_type[i] == 2)
			redir_2(re->re_file[i]);
		else if (re->re_type[i] == 3)
			redir_3(re->re_file[i]);
		i++;
	}
	return (1);
}

void	parsing_cmd(t_data *data, int idx)
{
	t_re re;

	get_redirect(data->cmds[idx], &re);
	free(data->cmds[idx]);
	data->cmds[idx] = re.cmd_j;
	redir_exec(&re);
}


//1. red - cmd
//2. red // cmd


// int		main(int argc, char **argv, char **envp)
// {
// 	if (argc > 1 && argv[1])
// 		return (0);
// 	char *str = ft_strdup("cat -e >>s ms_get_re.c");
// 	parsing_cmd(str, envp);
// 	return (0);
// }