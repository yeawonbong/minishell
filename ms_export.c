#include "minishell.h"

char	*ft_reunion(char **strarr, int strnum)
{
	char	*ret;
	char	*temp;
	int	i;

	ret = ft_strdup(strarr[0]);
	i = 1;
	while (i < strnum)
	{
		temp = ft_strjoin(temp, strarr[i]);
		free (ret);
		ret = temp;
		i++;
	}
	return (ret);
}

char	*ft_replace(t_data *data, char *var)
{
	int	i;
	int	j;
/*
$USER

**env
sma=aaasds
USER=ybong
*/
	i = 0;
	j = 0;
	while (data->env[i])
	{
		while (data->env[i][j] && data->env[i][j] != '=')
			j++;
		if (!ft_strncmp(data->env[i], var, ft_strlen(var)))
		{
			free(var);
			var = ft_strdup(data->env[i] + j + 1);
			return (var);
		}
		j = 0;
		i++;
	}
	return (NULL);
}

char	*ft_replace_envar(t_data *data, char *envar)
{
	char    **split_equal;
	char	**split_dollar;

	char    *var;
	char	*replace;
	int		tojoin;
	int 	i;
	int		j;

//s$USERma$sddf$asads="asd$USERas=asdads"
	i = 0;
	j = 0;
	split_equal = (char**)malloc(sizeof(char*) * 3);
	split_equal[2] = NULL;
	while (envar[i] == '=')
		i++; //equal index
	split_equal[0] = ft_substr(envar, 0, i);
	split_equal[1] = ft_strdup(&envar[i + 1]); // =기준으로 자름
	i = 0;
	while (i < 2)
	{
		if (*split_equal[i] == '$')
			tojoin = 1;
		if (ft_strchr(split_equal[i], '$'))
			split_dollar = ft_split(split_equal[i], '$');
		while (split_dollar[tojoin])
		{
			split_dollar[tojoin] = ft_replace(data, split_dollar[tojoin]); //없으면 0 들어감
			tojoin++;
		}
		free(split_equal[i]);
		split_equal[i] = ft_reunion(split_dollar, tojoin);
		tojoin = 0;
		i++;
	}
	char *res;
	res = ft_reunion(split_equal, 2);
	return (res);
	//return (ft_reunion(split_equal, 2));
	//split equals 합쳐
			//sma=ar$USER
}

void	ft_export(t_data *data, char *buf)
{
	char	**exp;
	char	**temp;
	int		i;

	exp = ft_split(buf, ' ');
	i = 0;
	while (exp[i])
		i++;
	if (i == 1) // 그냥 export면 출력
	{
		while (data->env[i])
			printf("%s\n", data->env[data->sort_env[i++]]);
		free(exp[0]);
	}
	else // export 뒤에 인자가 있다면 -> 환경변수 추가
	{
		temp = (char **)malloc(sizeof(char *) * (data->env_height + i));// 2갠데 null까지 3
		temp[data->env_height + i - 1] = NULL;
		ft_copy_env(data->env, temp);
		i = 1;
		while (exp[i])
		{
			// if ('')
				//sma=aaa$USER
			if (*exp[i] == '=')
			{
				printf("minishell: bad assignment\n");
				return ;
			}
			else if (ft_strchr(exp[i], '='))
			{
				if (ft_strchr(exp[i], '$')) 
				{	
					free(exp[i]);
					exp[i] = ft_replace_envar(data, exp[i]); // 환경변수 있으면 replace
				}
				printf("add_env = %s, (i = %d)\n", exp[i], i);
				temp[data->env_height] = ft_strdup(exp[i]); // add_envar
				data->env_height++;
			}
			// else // = 가 없는 경우? 넣을까 말까 - 안넣는 쪽으로 생각중
			i++;
		}
		temp[data->env_height] = NULL;
		ft_split_free(data->env);
		data->env = temp;
		free(data->sort_env);
		ft_sort_env(data);
	}
	free(exp);
}
