#include "../minishell.h"

void	ft_cd(t_data *data)
{
	char	**cd_args;
	int		i;
	char	*path;

	i = 0;
	cd_args = ft_split(data->cmds[data->idx], ' ');
	if (cd_args[1] == NULL)
	{
		while (data->env[i])
		{
			if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
			{
				path = data->env[i] + 5;
				break ;
			}
			i++;
		}
		chdir(path);
		return ;
	}
	chdir(cd_args[1]);
	ft_split_free(cd_args);
}

int check_builtin(char *buf)
{
	if ((!(ft_strncmp(buf, "export", 6)) && (!*(buf + 6) || *(buf + 6) == ' '))\
	|| (!(ft_strncmp(buf, "unset", 5)) && (!*(buf + 5) || *(buf + 5) == ' '))\
	|| (!(ft_strncmp(buf, "env", 3)) && (!*(buf + 3) || *(buf + 3) ==' ' ))\
	|| (!(ft_strncmp(buf, "cd", 2)) && (!*(buf + 2) || *(buf + 2) == ' '))\
	|| (!(ft_strncmp(buf, "exit", 4)) && (!*(buf + 4) || *(buf + 4) == ' ')))
		return(1);
	return(0);
}

void	ft_builtins(t_data *data)
{
	pid_t	pid;
	int		i;
	char	*cmd;

	i = data->idx;
	cmd = ft_strtrim(data->cmds[i], " ");
	if (!(ft_strncmp(cmd, "exit", 4)) \
	&& (!*(cmd + 4) || *(cmd + 4) == ' '))
	{
		printf("exit\n");
		exit(0);
	}
	if (!(ft_strncmp(cmd, "export", 6)) \
	&& (*(cmd + 6) || *(cmd + 6) == ' '))
	{
		ft_export(data, 0);
		free(cmd);
		return ;
	}
	else if (!(ft_strncmp(cmd, "unset", 5)) && (!*(cmd + 5) || *(cmd + 5) ==' ' ))
	{
		ft_unset(data, cmd);
		return ;
	}
	printf("builtin_fork\n");
	pid = fork();
	if (pid == 0)
	{
		if (data->cmds[data->idx + 1] != NULL)
		{
			dup2(data->fd[1], STDOUT_FILENO);
			close(data->fd[0]);
		}
		if (!(ft_strncmp(cmd, "export", 6)) && (!*(cmd + 6)))
		{
			ft_export(data, 1);
		}
		else if (!(ft_strncmp(cmd, "env", 3)) && (!*(cmd + 3) || *(cmd + 3) ==' ' ))
			ft_env(data);
		else if (!(ft_strncmp(cmd, "cd", 2)) && (!*(cmd + 2) || *(cmd + 2) == ' '))
			ft_cd(data);
		exit(1);
	}
	else
		wait(0);
	free(cmd);
}
