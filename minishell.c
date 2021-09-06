#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*buf;
	pid_t	pid = 0;
	int		fd[2]; 
	int		i;
	int		flag = 0;
	char	output[BUFSIZE];

	if (1 < argc || argv[1])
		return (0);
	pid = 0;
	buf = NULL;
	ft_filldata(&data, envp);
	while(1)
	{
		buf = readline("minishell $ "); //경로 넣어주기!! 해야함
		printf("original buf = %s|\n", buf);
		if (*buf)
			add_history(buf);
		if (ft_strchr(buf, '$'))
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
					if (data.idx > 0)
					{
						// printf("hello\n");
						close(fd[1]);
						dup2(fd[0], STDIN_FILENO);
						read(0, output, BUFSIZE);
						printf("output2 = %s\n", output);
						// close(old_fd[0]);
						// close(old_fd[1]);
					}
					if (data.cmds[data.idx + 1] != NULL)
					{
						close(fd[0]);
						dup2(fd[1], STDOUT_FILENO);
						// close(fd[1]);
					}
				}
				// < 
				run_cmd(envp, &data);
				printf("run_cmd\n");
// 			ft_putstr_fd("here?\n", data.stdio[1]);
// printf("PATH  = %s\n", data.path);
				if (execve(data.path, data.cmd_args, envp) == -1)
					perror("execve error :");
				free(data.path);
				ft_split_free(data.cmd_args);
				// free(buf);
			}// pipe니까 다른 프로세스끼리 보낼 수 있다고.
			// ft_putstr_fd("?\n", data.stdio[1]);
			wait(0);
			// printf("flag = %d\n", data.pipe_flag);
			if (data.pipe_flag)
			{
				// close(fd[1]);
				// printf("hello\n");
				flag = 1;
				data.pipe_flag--;
				// old_fd[0] = fd[0];
				// old_fd[1] = fd[1];
				// close(fd[0]);
				// close(fd[1]);
				// dup2(fd[0], STDIN_FILENO);
				// dup2(fd[1], fd[0]);
				// dup2(fd[0], data.stdio[0]);
				
				// fd[1] = dup(fd[0]);
				///////////////
				// read(fd[0], output, BUFSIZE); // 표준 입력(-현재 fd[0])을 읽어
				// printf("output = %s", output);
			}
			if (data.redirect_flag)
			{
				dup2(data.stdio[0], STDIN_FILENO);
				dup2(data.stdio[1], STDOUT_FILENO);
			}
			free(data.cmds[data.idx]);
			data.idx++;
		}
		free(buf);
		free(data.cmds);
	}
	return (0);
}
