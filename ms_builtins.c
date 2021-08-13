#include "minishell.h"

void	ft_split_free(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);	
}
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
	int		i;

	i = 0;
	if (*(buf + 6)) //	export $USER=ss (환경변수 추가)
	{
		exp = ft_split(buf, ' ');
			printf("=========ppp1\n");
		// export
		// hi=u
		// ue=asdad
		// NULL   i= 3
		while (exp[i])
			i++;
			printf("=========ppp2\n");
		temp = (char **)malloc(sizeof(char *) * data->env_height + i);
		temp[data->env_height + i - 1] = NULL;
			printf("=========ppp3\n");
		ft_copy_env(data->env, temp); //segfault 구간
			printf("=========ppp4\n");
		ft_split_free(data->env);
			printf("=========ppp5\n");
		i = 1;
		while (exp[i])
		{
			printf("=========p1\n");
			if (ft_strchr(exp[i], '='))
			{
				temp[data->env_height++] = ft_strdup(exp[i]);
				printf("(((((add_env : %s))))))\n", exp[i]);
			}
			else
			{
				temp[data->env_height++] = ft_strjoin(exp[i], "=\'\'");
			}
			i++;
		}
		ft_split_free(exp);
		printf("=========p2\n");
		data->env = temp;
		free(data->sort_env);
		ft_sort_env(data);
		printf("=========p3\n");
		i = 0;
		while (i < data->env_height)
			printf("TESTPRINT = %s\n", data->env[data->sort_env[i++]]);
	}
	else
	{
		while (data->env[i])
			printf("%s\n", data->env[data->sort_env[i++]]);
	}
	printf("=========p4\n");

}

// void	ft_unset()
// {
// }


// void	ft_exit()
// {
// }

//export set과 unset, exit