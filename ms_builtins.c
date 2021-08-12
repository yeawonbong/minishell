#include "minishell.h"

int		longer_len(char *str, char *str2)
{
	int s;
    int s2;

    s = ft_strlen(str);
    s2 = ft_strlen(str2);
    if (s > s2)
        return (s);
    else
        return (s2);
}

void	ft_sort_env(t_data *data)
{
	int temp;
	int i;
	int j;

	i = -1;
	j = 0;
	data->sort_env = (int *)malloc(sizeof(int) * data->env_height);
    while (i++ < data->env_height)
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

void	ft_export(t_data *data, char *buf)
{
	char	**exp;
	char	**temp;
	char	*join;
	int		i;

	i = 0;
	if (*(buf + 6)) //	export $USER=ss (환경변수 추가)
	{
		exp = ft_split(buf, ' ');
		while (exp[i])
			i++;
		temp = (char **)malloc(sizeof(char *) * data->env_height + i);
		ft_copy_env(data->env, temp);
		i = 1;
		while (exp[i])
		{
			if (ft_strchr(exp[i], '='))
			{
				temp[data->env_height++] = exp[i];
				printf("(((((add_env : %s))))))\n", exp[i]);
			}
			else
			{
				temp[data->env_height++] = (join = ft_strjoin(exp[i], "=\'\'"));
				free(join);
			}
			i++;
		}
		temp[data->env_height] = NULL;
		free(data->env);
		data->env = temp;
		free(exp);
		free(data->sort_env);
		ft_sort_env(data);
	
		while (data->env[i])
			printf("TESTPRINT = %s\n", data->env[data->sort_env[i++]]);
	
	}
	else
	{
		while (data->env[i])
			printf("%s\n", data->env[data->sort_env[i++]]);
	}
	// exit(0);
}

// void	ft_unset()
// {
// }


// void	ft_exit()
// {
// }

//export set과 unset, exit