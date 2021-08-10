#include "minishell.h"

// char	**ft_fillcmd(char *buf)
// {
// 	char	**cmd;
// 	int		i;

// 	i = 0;
// 	cmd = ft_split(buf, '|');
// 	while(cmd[i]) //함수 따로 빼기
// 	{
// 		char *temp=0;
// 		temp = ft_strtrim(cmd[i], " ");
// 		free(cmd[i]);
// 		cmd[i] = temp;
// 		printf("split = %s0\n", cmd[i]);
// 		i++;
// 	}
// 	return(cmd);
// }


int	main()
{
	char	*buf;
	pid_t	pid = 0;
	char	**cmd;
	int		i;
	int		fd[2]; 
	char	output[BUFSIZE];
	char	*ptr;



	i = 0;
	pid = 0;
	buf = NULL;
	pipe(fd); // fd[1] >-----------> fd[0]
	while(1)
	{
		buf = readline("minishell $ ");
		cmd = ft_split(buf, '|');
		while(cmd[i]) //함수 따로 빼기
		{
			char *temp=0;
			temp = ft_strtrim(cmd[i], " ");
			free(cmd[i]);
			cmd[i] = temp;
			printf("split = %s0\n", cmd[i]);
			i++;
		}
		//부모 input (cat test.c) pipe 출력 --> grep
		// cmd = ft_fillcmd(buf);
		i = 0;
		while (cmd[i])
		{
			ft_memset(output, 0, BUFSIZE);
			pid = fork();
			if (pid == 0)
			{
				ptr = cmd[i];
				dup2(fd[1], STDOUT_FILENO); // 표준 출력을 fd[1]로
				close(fd[0]);
				if (!ft_strncmp(cmd[i], "echo ", 5))
					ft_echo(cmd[i]);
				else if (!ft_strncmp(cmd[i], "cd ", 3))
					ft_cd(cmd[i]);
				else if (!ft_strncmp(cmd[i], "pwd", 3))
					ft_pwd();
				else
					exit(1);
				// else if ((!ft_strncmp(buf, "export ", 7)))
				// 	ft_export(); //unset
				// else if (!(ft_strncmp(cmd[i], "env ", 4)))
				// 	ft_
				exit(0);
			}// pipe니까 다른 프로세스끼리 보낼 수 있다고.
			wait(0);
			read(fd[0], output, 1024); // 표준 입력(-현재 fd[0])을 읽어
			printf("output = %s", output);
			free(cmd[i]);
			i++;
		}
		add_history(buf);
		free(buf);
		free(cmd);
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

