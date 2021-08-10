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

int     ft_env_height(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        i++;
    }
    return (i);
}

void	ft_sort_env(char **envp, t_data *data)
{
	int env_height;
	int temp;
	int i;

	i = -1;
	env_height = ft_env_height(envp);
	data->sort_env = (int *)malloc(sizeof(int) * env_height);
    while (i++ < env_height)
        data->sort_env[i] = i;
	while (0 < env_height)
	{
        i = 0;
        while (i < env_height - 1)
        {
		    if (0 < ft_strncmp(envp[data->sort_env[i]], envp[data->sort_env[i + 1]], longer_len(envp[i], envp[i + 1])))
		    {
			    temp = data->sort_env[i];
			    data->sort_env[i] = data->sort_env[i + 1];
			    data->sort_env[i + 1] = temp;
		    }
		    i++;
        }
        env_height--;
	}
}

void	ft_export(char **envp, t_data *data, char *buf)
{

	if (*(buf + 6)) //	export $USER=ss (환경변수 추가)
	{
		//환경변수추가 -> **envp 끝에 write;
		free(data->sort_env);
		ft_sort_env(envp, data);
	}
	//print 정렬된 env
}

// void	ft_unset()
// {
// }


// void	ft_exit()
// {
// }

//export set과 unset, exit