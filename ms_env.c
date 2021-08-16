#include "minishell.h"

void    ft_env(t_data *data, char *buf)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i++]);
	}
}
