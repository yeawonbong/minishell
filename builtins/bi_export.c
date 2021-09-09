#include "../minishell.h"

void	ft_export(t_data *data, int child)
{
	char	**exp_arg;
	char	**tempenv;
	int		add;
	int		i;

printf("======================\n");
//data->cmds 
	exp_arg = ft_split(data->cmds[data->idx], ' ');
	add = 0;
	i = 0;
	while (exp_arg[i])
	{
		printf("보자 : %s\n", exp_arg[i]);
		if (ft_strchr(exp_arg[i], '='))
			add++;
		i++;
	}
	if (i == 1 && child) // 그냥 export면 , 자식 프로세스에서 출력
	{
		printf("HERE\n");
		i = 0;
		while (data->env[i])
			printf("%s\n", data->env[data->sort_env[i++]]);
	}
	else // export 뒤에 인자가 있다면 -> 환경변수 추가
	{
		tempenv = (char **)malloc(sizeof(char *) * (data->env_height + add + 1));// 2갠데 null까지 3
		// tempenv[data->env_height + add - 1] = NULL;
		ft_copy_env(data->env, tempenv);
		i = 1;
		while (exp_arg[i])
		{
			printf("hihi\n");
			if (*exp_arg[i] == '=')
			{
				printf("minishell: bad assignment\n");
				return ;
			}
			else if (ft_strchr(exp_arg[i], '='))
			{
				printf("add_env = %s, (i = %d)\n", exp_arg[i], i);
				tempenv[data->env_height] = ft_strdup(exp_arg[i]); // add_envar
				data->env_height++;
			}			// else // = 가 없는 경우? 넣을까 말까 - 안넣는 쪽으로 생각중
			i++;
		}
		tempenv[data->env_height] = NULL;
		ft_split_free(data->env);
		data->env = tempenv;
		free(data->sort_env);
		ft_sort_env(data);
	}
	free(exp_arg);
}

void	ft_unset(t_data *data, char *buf)
{
	buf = 0;
	char	**unset_arg;
	char	**tempenv;
	char	*var;
	int		i;
	int		j;
	int		k;
	int		t;

	tempenv = NULL;
	i = 0;
	t = 0;
	unset_arg = ft_split(data->cmds[data->idx], ' '); 
	while (unset_arg[i]) // count vars to unset
		i++;
	if (i == 1)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDOUT_FILENO);
		// return ;
	}
	else
	{
		data->env_height -= --i;
		printf("HEIGHT = %d\n", data->env_height);
		tempenv = (char **)malloc(sizeof(char *) * (data->env_height + 1));
		tempenv[data->env_height] = NULL;
		i = 0;//unset >USER PATH
		while (data->env[i])
		{
			j = 0;
			while(data->env[i][j] != '=')
				j++;
			var = ft_substr(data->env[i], 0, j);
			k = 1;
			while (unset_arg[k])
			{
				if (!ft_strncmp(var, unset_arg[k], longer_len(var, unset_arg[k]))) // 같으면
					break;
				k++;
			}
			if (!unset_arg[k])
			{
				tempenv[t] = ft_strdup(data->env[i]); //++?
				t++;
			}
			i++;
		}
		free(var);
		ft_split_free(data->env);
		data->env = tempenv;
		free(data->sort_env);
		ft_sort_env(data);
	}
	ft_split_free(unset_arg);
}