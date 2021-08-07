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
