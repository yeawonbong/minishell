#include "minishell.h"

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
	j = 0;	
	data->sort_env = (int *)malloc(sizeof(int) * data->env_height);
    while (i++ < data->env_height - 1)
        data->sort_env[i] = i;
	while (0 < data->env_height - j)
	{
        i = 0;
        while (i < data->env_height - 1)
        {
		    if (0 < ft_strncmp(data->env[data->sort_env[i]], data->env[data->sort_env[i + 1]], longer_len(data->env[i], data->env[i + 1])))
		    {
			    temp = data->sort_env[i];
			    data->sort_env[i] = data->sort_env[i + 1];
			    data->sort_env[i + 1] = temp;
		    }
		    i++;
        }
        j++;
	}
}

void	ft_filldata(t_data *data, char **envp) //이름수정할래
{
	// -3 / 3
	// -
	// -
	// - NULL
	//복사
	int		i;

	i = 0;
	data->env_height = ft_strarr_height(envp);
	data->env = (char **)malloc(sizeof(char*) * (data->env_height + 1));
	data->env[data->env_height] = NULL;
	printf("height=%d\n", data->env_height);
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	// printf("iii=%d\n", i);
	// // ft_copy_env(envp, data->env);
	ft_sort_env(data);
	return ;
}

// void	ft_unset()
// {
// }


// void	ft_exit()
// {
// }

//export set과 unset, exit