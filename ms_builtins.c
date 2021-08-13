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

void	ft_export(t_data *data, char *buf)
{
	char	**exp;
	char	**temp;
	int		i;

	i = 0;
	if (*(buf + 6)) //	export $USER=ss (환경변수 추가)
	{
		exp = ft_split(buf, ' ');
		while (exp[i])
			i++; 
		temp = (char **)malloc(sizeof(char *) * (data->env_height + i));// 2갠데 null까지 3
		temp[data->env_height + i - 1] = NULL;
		ft_copy_env(data->env, temp); //segfault 구간
		ft_split_free(data->env);
		i = 1;
		while (exp[i])
		{
			// if ('')
			if (ft_strchr(exp[i], '='))
			{

				/*sma=aaa$USER
				
				split'='
			sma
			aaa$USERech
			strchr($) *pointer strcmp **env, =이후 치환

 			split$ --- free
			V	aaa - strjoin - env에서 찾은 = 뒤에것
				aaa
				USER **env

			
				*/
					char * = p~NULL || p~'=' 환경변수
					(data->env)**env에서 찾는다. 
					if 있으면 대치
					else 없앤다.
			}
			if (*exp[i] == '=')
			{
				printf("minishell: bad assignment\n");
				return ;
			}
			if (ft_strchr(exp[i], '='))
			{
				if (ft_strchr(exp[i], '$'))
					ft_replace_envar(data, exp[i]);
				temp[data->env_height++] = ft_strdup(exp[i]);
			}
			i++;
		}
		temp[data->env_height] = NULL;
		ft_split_free(exp);
		data->env = temp;
		free(data->sort_env);
		ft_sort_env(data);
	}
	else
	{
		while (data->env[i])
			printf("%s\n", data->env[data->sort_env[i++]]);
	}
}

// void	ft_unset()
// {
// }


// void	ft_exit()
// {
// }

//export set과 unset, exit