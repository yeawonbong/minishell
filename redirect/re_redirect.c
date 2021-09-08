#include "../minishell.h"

void	redir_1(char *file)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("error : %s %d\n", strerror(errno), errno);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_2(char *file)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("error : %s %d\n", strerror(errno), errno);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_3(char *file)
{
	int		fd;

	fd = open(file, O_RDWR, 0644);
	if (fd < 0)
	{
		printf("error : %s %d\n", strerror(errno), errno);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	get_buf(int re_fd[2], char *buf, int fd, char *str)
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

void	redir_4(char *str)
{
	int		re_fd[2];
	pid_t	pid;
	char	*buf;
	int		fd;

	buf = NULL;
	fd = dup(STDOUT_FILENO);
	pipe(re_fd);
	pid = fork();
	if (pid == 0)
		get_buf(re_fd, buf, fd, str);
	else
		wait(0);
	dup2(re_fd[0], STDIN_FILENO);
	close(re_fd[1]);
}
