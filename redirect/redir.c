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

	printf("hello redir4\n");
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

void	redir_4(char *str)
{
	int	re_fd[2];
	pid_t	pid;
	char	*buf;
	int		fd;
	// char temp[1024];÷

	fd = dup(STDOUT_FILENO);
	pipe(re_fd);
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			buf = readline("> ");
			if (ft_strlen(buf) == ft_strlen(str))
			{
				if (ft_strncmp(buf, str, ft_strlen(str)) == 0)
				{	
					free(buf);
					exit(0);
				}
			}
			dup2(re_fd[1], STDOUT_FILENO);
			close(re_fd[0]);
			printf("%s\n", buf);
			free(buf);
			dup2(fd, STDOUT_FILENO);
		}
	}
	else
		wait(0);
	dup2(re_fd[0], STDIN_FILENO);
	close(re_fd[1]);
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
		else if (re->re_type[i] == 4)
			redir_4(re->re_file[i]);
		i++;
	}
	return (1);
}

void	redirect(t_data *data, int idx)
{
	t_re re;

	get_redirect(data->cmds[idx], &re);
	free(data->cmds[idx]);
	data->cmds[idx] = re.cmd_j;
	redir_exec(&re);

}
