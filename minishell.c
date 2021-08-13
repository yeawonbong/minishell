#include "minishell.h"

int     ft_env_height(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_copy_env(char **src, char **dest)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	return ;
}

void	ft_filldata(t_data *data, char **envp) //이름수정할래
{
	
	//복사
	data->env_height = ft_env_height(envp);
	data->env = (char **)malloc(sizeof(char*) * data->env_height + 1);
	data->env[data->env_height] = NULL;
	ft_copy_env(envp, data->env);
	ft_sort_env(data);
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
	
	ft_filldata(&data, envp);
	while(1)
	{
		buf = readline("minishell $ "); //경로 넣어주기!! 해야함
		if (*buf)
			add_history(buf);
		data.cmds = ft_split(buf, '|');
		printf("cmds[0] = %s\n", data.cmds[0]);
		i = 0;
		while (data.cmds[i]) // ls | grep "minishell" | cat -> (ls, NULL) -> (grep, "minishell") -> (cat ,NULL)
		{
			ft_memset(output, 0, BUFSIZE);
			if (!(ft_strncmp(buf, "export", 6)))
			{
				ft_export(&data, buf); //unset
				break;
			}
			else
			{
				printf("hello1\n");
				pid = fork();
			}
			if (pid == 0)
			{
				dup2(fd[1], STDOUT_FILENO); // 표준 출력을 fd[1]로
				close(fd[0]);
				if (!(ft_strncmp(buf, "export", 6)))
					ft_export(&data, buf); //unset
				else
				{
					run_cmd(envp, &data);
					if (execve(data.path, data.cmd_args, envp) == -1)
						perror("execve error :");
				}
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

