#include "minishell.h"

void	ft_filldata(t_data *data, char **envp) //이름수정할래
{
	int		i;

	i = 0;
	data->idx = 0;
	data->path = 0;
	data->env_height = ft_strarr_height(envp);
	data->env = (char **)malloc(sizeof(char*) * (data->env_height + 1));
	data->env[data->env_height] = NULL;
	printf("height=%d\n", data->env_height);
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	data->stdio[0] = dup(STDIN_FILENO);
	data->stdio[1] = dup(STDOUT_FILENO);
	data->pipe_flag = 0;
	data->redirect_flag = 0;
	ft_sort_env(data);
	return ;
}