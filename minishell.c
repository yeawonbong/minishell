#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*buf;
	pid_t	pid = 0;
	int		fd[2]; 
	int		i;
	char	output[BUFSIZE];

	if (1 < argc || argv[1])
		return (0);
	pid = 0;
	buf = NULL;
	pipe(fd); // fd[1] >-----------> fd[0]
	
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
		data.cmds = ft_split(buf, '|'); //cmd token -> |랑 ;단위로 쪼개야함.
		for (int n = 0; data.cmds[n]; n++)
			printf("cmds[%d] = %s\n", n, data.cmds[n]);
		i = 0;
		while (data.cmds[i]) // ls | grep "minishell" | cat -> (ls, NULL) -> (grep, "minishell") -> (cat ,NULL)
		{
			ft_memset(output, 0, BUFSIZE);
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
				pid = fork();
			}
			if (pid == 0)
			{
				dup2(fd[1], STDOUT_FILENO); // 표준 출력을 fd[1]로
				close(fd[0]);
				// check_redir(&data, i);
				run_cmd(envp, &data);
				if (execve(data.path, data.cmd_args, envp) == -1)
					perror("execve error :");
				free(data.path);
				ft_split_free(data.cmd_args);
			}// pipe니까 다른 프로세스끼리 보낼 수 있다고.
			wait(0);
			read(fd[0], output, BUFSIZE); // 표준 입력(-현재 fd[0])을 읽어
			printf("output = %s", output);
			free(data.cmds[i]);
			i++;
		}
		free(buf);
		free(data.cmds);
	}
	return (0);
}
