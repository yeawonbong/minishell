#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*buf;
	pid_t	pid = 0;
	int		fd[2]; 
	int		i;
	int		temp[2];
	// int		flag = 0;
	char	output[BUFSIZE];

	if (1 < argc || argv[1])
		return (0);
	pid = 0;
	buf = NULL;
	ft_filldata(&data, envp);
	temp[0] = dup(STDIN_FILENO);
	temp[1] = dup(STDOUT_FILENO);
	while(1)
	{
		buf = readline("minishell $ "); //경로 넣어주기!! 해야함
		printf("original buf = %s|\n", buf);
	
		if (*buf)
			add_history(buf);
		if (ft_strchr(buf, '$') && *buf)
			buf = ft_modify_buf(&data, buf);
		printf("modified buf = %s|\n", buf);

		data.pipe_flag = 0;
		i = 0;
		while (buf[i])
		{
			if (buf[i] == '|')
				data.pipe_flag++;
			i++;
		}
		data.pipe_flag++;
		printf("flag = %d\n", data.pipe_flag);
		data.cmds = ft_split(buf, '|'); //cmd token -> |랑 ;단위로 쪼개야함.
		i = 0;
		data.idx = 0;
		while (data.cmds[data.idx]) // ls | grep "minishell" | cat -> (ls, NULL) -> (grep, "minishell") -> (cat ,NULL)
		{
			pipe(fd); // fd[1] >-----------> fd[0]
			data.redirect_flag = 0;
			if (ft_strchr(data.cmds[data.idx], '<') || ft_strchr(data.cmds[data.idx], '>'))
			 	data.redirect_flag = 1;
			ft_memset(output, 0, BUFSIZE);
			if (data.redirect_flag)
				parsing_cmd(&data, i); //redirect 처리
			if (!(ft_strncmp(buf, "export", 6)) && (!*(buf + 6) || *(buf + 6) == ' '))
			{
				ft_export(&data, buf);
				break;
			}
			if (!(ft_strncmp(buf, "unset", 5)) && (!*(buf + 5) || *(buf + 5) == ' '))
			{
				ft_unset(&data, buf);
				break;
			}
			else if ((ft_strncmp(buf, "env", longer_len("env", buf)) == 0))
			{
				ft_env(&data);
				break;
			}//
			else
			{
				printf("fork!\n");
				printf("current cmd = %s, idx = %d\n", data.cmds[data.idx], data.idx);
				pid = fork();
			}
			if (pid == 0)
			{
				if (data.pipe_flag)
				{
					if (data.cmds[data.idx + 1] != NULL)
					{
						dup2(fd[1], STDOUT_FILENO);
						close(fd[0]);
						close(fd[1]);
					}
				}
				// < 
				run_cmd(envp, &data);
				if (execve(data.path, data.cmd_args, envp) == -1)
					perror("execve error :");
				free(data.path);
				ft_split_free(data.cmd_args);
			}// pipe니까 다른 프로세스끼리 보낼 수 있다고.
			else
				wait(0);
			if (data.pipe_flag)
			{
				data.pipe_flag--;
				if (data.cmds[data.idx + 1] != NULL)
				{
					dup2(fd[0], STDIN_FILENO);
					close(fd[1]);
					close(fd[0]);
				}
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
