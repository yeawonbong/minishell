#include "minishell.h"

void	ft_fillcmds(char *buf, t_data *data, char **envp) //이름수정할래
{
	char	*temp;
	int		i;
	int j = 0;
	temp = 0;
	i = 0;
	data->cmds = ft_split(buf, '|');
	 //함수 따로 빼기
	
	printf("split = %s0\n", data->cmds[i]);
	ft_sort_env(envp, data);//////
	while(envp[j])
	{
		printf("(%d)sort_env = %s\n", j ,envp[data->sort_env[j]]);
		j++;
	}
	return ;
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*buf;
	pid_t	pid = 0;
	int		i;
	int		fd[2]; 
	char	output[BUFSIZE];

//초반에 env_sort 세팅
	if (1 < argc || argv[1])
		return (0);
	pid = 0;
	buf = NULL;
	pipe(fd); // fd[1] >-----------> fd[0]
	while(1)
	{
		buf = readline("minishell $ "); //경로 넣어주기!! 해야함
		ft_fillcmds(buf, &data, envp);
		printf("cmds[0] = %s\n", data.cmds[0]);
		i = 0;
		while (data.cmds[i]) // ls | grep "minishell" | cat -> (ls, NULL) -> (grep, "minishell") -> (cat ,NULL)
		{
			ft_memset(output, 0, BUFSIZE);
			pid = fork();
			if (pid == 0)
			{
				dup2(fd[1], STDOUT_FILENO); // 표준 출력을 fd[1]로
				close(fd[0]);
				run_cmd(envp, &data);
				if (!(ft_strncmp(buf, "export", 6)))
					ft_export(envp, &data, buf); //unset
				else if (execve(data.path, data.cmd_args, envp) == -1)
				{
					perror("execve error :");
				}
			}// pipe니까 다른 프로세스끼리 보낼 수 있다고.
			wait(0);
			read(fd[0], output, BUFSIZE); // 표준 입력(-현재 fd[0])을 읽어
			printf("output = %s", output);
			free(data.cmds[i]);
			i++;
		}
		add_history(buf);
		free(buf);
		free(data.cmds);
	}
}
// cat < file1
// grep "hello"
// wc -l
// cat < file1 | grep "hello" | wc -l // 2차배열의 포인터배열 (3) split 파이프 기준으로 자르고, 처리를 해준다. 

// p = strchr(" ") + 1


// {cat, <, file1} 2차 //명령 다음에 < > 있는가. 
// {grep, "hello"}



		// PWD=/Users/ybong/Desktop/minishell


// *buf
// | < 
// ls -al | grep "minishell" | wc -l

// ls -al 
// -rwxr-xr-x   1 ybong  staff  49936 Aug  6 14:35 minishell
// -rw-r--r--   1 ybong  staff  43040 Aug  6 14:35 minishell.a
// -rw-r--r--   1 ybong  staff    757 Aug  6 14:38 minishell.c
// -rw-r--r--   1 ybong  staff    240 Aug  6 14:36 minishell.h


// 부모
// pipe 검사 2 //+1 (3)
// i / o

// 자식			자식			자식
// i / o		  i / o			i / o

// dup2

// pipe 

// fd
// f = 

// process =  = 
// PATH=
// 	/usr/local/bin/cat
// 	/usr/bin/cat
// 	/bin/cat
// 	/usr/sbin/cat
// 	/sbin/cat

