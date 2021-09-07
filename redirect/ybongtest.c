#include "../minishell.h"

int main(int argc, char **argv, char **envp)
{
	char **lss = ft_split("cat", ' ');
	char **wcc = ft_split("wc", ' ');
	int stdio[2];
	int fd[2];
	int	old_fd[2];
	char	str[100];
	char out[BUFSIZE];

	// for (int i=0; *cmds[i]; i++)
	// printf("cmds = %s\n", cmds[i]);
	stdio[0] = dup(STDIN_FILENO);
	stdio[1] = dup(STDOUT_FILENO);

	// printf("he");
  	pipe(fd);
	// while(1)
	// {
		int pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			// dup2(fd[0], STDIN_FILENO);
	// printf("fd0 = %d\n", fd[0]);

			execve("/bin/ls", lss, envp);

		}
		else
			wait(0);
	// printf("fd0 = %d\n", fd[0]);
		// dup2(fd[1], STDOUT_FILENO);
	// dup2(stdio[1], STDOUT_FILENO);

		// pipe(fd);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		pid = fork();  // dup2(fd[0], STDIN_FILENO);
		if (pid == 0)  
		{
			// old_fd[0] = fd[0];
			// close(old_fd[0]);
			execve("/usr/bin/wc", wcc, envp);
			// printf("where\n");
		}
		else if(pid > 0)
			wait(0);
		dup2(stdio[0], STDIN_FILENO);
		scanf("%s", str);
		printf("parent\n");
		printf("SCANF TEST : %s", str);
		// usleep(100);
			// ft_putstr_fd("hi", STDOUT_FILENO);
	// read(fd[0], out, BUFSIZE);
	// dup2(stdio[1], STDOUT_FILENO);
	// printf("OUT = %s\n", out);
	// }
return 0;
}
