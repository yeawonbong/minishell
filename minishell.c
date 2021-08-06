#include "minishell.h"

void	ft_echo(char *buf)
{
	if (!ft_strncmp(buf, "echo -n ", 8))
		printf("%s", buf + 8);
	else 
		printf("%s\n", buf + 5);
}

void	ft_cd(char *buf)
{
	chdir(buf + 3);
	printf("change dir\n");
}

void	ft_pwd(void)
{
	char cwd[BUFSIZE];

	getcwd(cwd, BUFSIZE);
	printf("%s\n", cwd);
}

int	main(char **envp)
{
	char	*buf;
	// pid_t	pid;

	buf = NULL;
	while(1)
	{
		if (buf)
			free(buf);
		buf = readline("enter a line :");
		if (!ft_strncmp(buf, "echo ", 5))
			ft_echo(buf);
		else if (!ft_strncmp(buf, "cd ", 3))
			ft_cd(buf);
		else if (!ft_strncmp(buf, "pwd ", 3))
			ft_pwd();
		// else if ((!ft_strncmp(buf, "export ", 7))) 보류
		add_history(buf);
	}
}

		// pid = fork();
		// if (pid == 0) // 자식 프로세스
		// {
		// }
		// free(buf);

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

