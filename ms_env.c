#include "minishell.h"

void    ft_env(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i++]);
	}
}

void	ft_copy_env(char **src, char **dest)
{
	int	i;

	i = 0;
	// if (**dest)
	// 	ft_split_free(dest);
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	// ft_split_free(src);
	return ;
}

void	ft_sort_env(t_data *data)
{
	int temp;
	int i;
	int j;

	i = -1;
	data->sort_env = (int *)malloc(sizeof(int) * data->env_height);
	while (++i < data->env_height)
		data->sort_env[i] = i;
	j = 0;
	printf("OK\n");
	while (0 < data->env_height - j)
	{
		i = 0;
		while (i + 1 < data->env_height)
		{
			if (0 < ft_strncmp(data->env[data->sort_env[i]], data->env[data->sort_env[i + 1]], \
			longer_len(data->env[i], data->env[i + 1])))
			{
				temp = data->sort_env[i];
				data->sort_env[i] = data->sort_env[i + 1];
				data->sort_env[i + 1] = temp;
			}
			i++;
		}
		j++;
	}


	printf("envheight = %d\n", data->env_height);
	for (int a=0; a < data->env_height; a++)
	{
		printf("%d ", data->sort_env[a]);
	}
	printf("\n");
}

