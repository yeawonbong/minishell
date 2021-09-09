#include "minishell.h"

int check_builtin(char *buf)
{
	if ((!(ft_strncmp(buf, "export", 6)) && (!*(buf + 6) || *(buf + 6) == ' '))\
	|| (!(ft_strncmp(buf, "unset", 5)) && (!*(buf + 5) || *(buf + 5) == ' '))\
	|| (!(ft_strncmp(buf, "env", 3)) && (!*(buf + 3) || *(buf + 3) ==' ' ))\
	|| (!(ft_strncmp(buf, "cd", 2)) && (!*(buf + 2) || *(buf + 2) == ' '))\
	|| (!(ft_strncmp(buf, "exit", 4)) && (!*(buf + 4) || *(buf + 4) == ' ')))
	{
		printf("this is builtin\n");
		return(1);
	}
	printf("return 0\n");
	return(0);
}

void	ft_builtins(t_data *data, char *buf)
{
	pid_t pid;

	if (!(ft_strncmp(buf, "exit", 4)) && (!*(buf + 4) || *(buf + 4) == ' '))
	{
		printf("exit\n");
		exit(0);
	}

	// pid = fork();
	// if (pid == 0)
	// {
		if (data->cmds[data->idx + 1] != NULL)
		{
			dup2(data->fd[1], STDOUT_FILENO);
			close(data->fd[0]);
		}
		if (!(ft_strncmp(buf, "export", 6)) && (!*(buf + 6) || *(buf + 6) == ' '))
			ft_export(data, buf); // not buf, cmd[i]!!! fix it!
		else if (!(ft_strncmp(buf, "unset", 5)) && (!*(buf + 5) || *(buf + 5) ==' ' ))
			ft_unset(data, buf);
		else if (!(ft_strncmp(buf, "env", 3)) && (!*(buf + 3) || *(buf + 3) ==' ' ))
			ft_env(data);
		else if (!(ft_strncmp(buf, "cd", 2)) && (!*(buf + 2) || *(buf + 2) == ' '))
			ft_cd(data);
	// 	exit(1);
	// }
	// else
	// 	wait(0);
}

char	*get_cwd(void)
{
	char buf[BUFSIZE];
	char *ptr;

	getcwd(buf, BUFSIZE);
	ptr = buf;
	return (ptr);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*buf;
	pid_t	pid = 0;
	int		i;
	int		temp[2];

	if (1 < argc || argv[1])
		return (0);
	pid = 0;
	buf = NULL;
	ft_filldata(&data, envp);
	temp[0] = dup(STDIN_FILENO);
	temp[1] = dup(STDOUT_FILENO);
	while(1)
	{
		pipe(data.fd); // fd[1] >-----------> fd[0]
		printf("ybong_sma@%s", get_cwd());
		buf = readline("$ "); //경로 넣어주기!! 해야함
		if (*buf)
			add_history(buf);
		if (ft_strchr(buf, '$') && *buf)
			buf = ft_modify_buf(&data, buf);
		data.pipe_flag = 0;
		i = 0;
		data.cmds = ft_split(buf, '|'); //cmd token -> |랑 ;단위로 쪼개야함.
		i = 0;
		data.idx = 0;
		while (data.cmds[data.idx]) // ls | grep "minishell" | cat -> (ls, NULL) -> (grep, "minishell") -> (cat ,NULL)
		{
			data.redirect_flag = 0;
			if (ft_strchr(data.cmds[data.idx], '<') || ft_strchr(data.cmds[data.idx], '>'))
			 	data.redirect_flag = 1;
			if (check_builtin(data.cmds[data.idx]))
				ft_builtins(&data, data.cmds[data.idx]);
			else
			{
				printf("fork!\n");
				printf("current cmd = %s, idx = %d\n", data.cmds[data.idx], data.idx);
				pid = fork();
				if (pid == 0)
				{
					//안에 온다면, process 종료시키기
					if (data.redirect_flag)
						redirect(&data, i); //redirect 처리
					if (data.cmds[data.idx + 1] != NULL)
					{
						dup2(data.fd[1], STDOUT_FILENO);
						close(data.fd[0]);
					}
					// <<
					run_cmd(&data);
					if (execve(data.path, data.cmd_args, envp) == -1)
						perror("execve error :");
				
					// free(data.path);
					// ft_split_free(data.cmd_args);
				}// pipe니까 다른 프로세스끼리 보낼 수 있다고.
				else
					wait(0);
			}
			if (data.cmds[data.idx + 1] != NULL)
			{
				dup2(data.fd[0], STDIN_FILENO);
				close(data.fd[1]);
			}
			free(data.cmds[data.idx]);
			data.idx++;
		}
		dup2(temp[1], STDOUT_FILENO);
		dup2(temp[0], STDIN_FILENO);
		free(buf);
		free(data.cmds);
	}
	return (0);
}
