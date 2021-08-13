char	*ft_reunion(char **strarr)
{
	char	*ret;
	char	*temp;
	int	i;



	ret = ft_strdup(strarr[0]);
	// ft_strjoin(strarr[0], strarr[1]);
	i = 1;
	while (strarr[i])
	{
		temp = ft_strjoin(temp, strarr[i]);
		free (ret);
		ret = temp;
		i++;
	}
	return (ret);
}

char	*ft_check_envar(t_data *data, char *var)
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
		if (!ft_strncmp(data->env[i], var, ft_strlen(var)));
		{
			free(var);
			var = ft_strdup(data->env[i] + j + 1);
			return (1);
		}
		j = 0;
		i++;
	}
	return (NULL);
}

void    ft_replace_envar(t_data *data, char *envar)
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
	split_equal = (char*)malloc(sizeof(char*) * 3);
	split_equal[2] = NULL;
	while (envar[i] == '=')
		i++; //equal index
	split_equal[0] = ft_substr(envar, 0, i);
	split_equal[1] = ft_strdup(envar[i + 1]); // =기준으로 자름
	i = 0;
	while (i < 2)
	{//다시 짜자 split('$');
		if (*split_equal[i] == '$')
			tojoin = 1;
		if (ft_strchr(split_equal[i], '$'))
			split_dollar = ft_split(split_equal[i], '$');
		while (split_dollar[tojoin])
			ft_check_envar(data, split_dollar[tojoin++]); //없으면 0 들어감
	//
		free(split_equal[i]);
		split_equal[i] = ft_reunion(split_dollar);



		var = ft_strchr(split_equal[i], '$');
		if (var)
		{
			var += 1
			replace = ft_check_envar(data, var);
			if (replace)//환경변수가 env에 있다면  
			{
				while (split_equal[i][j] != '$')
					j++;
				var = ft_substr(split_equal[i], 0, j);
				free(split_equal[i]);
				split_equal[i] = ft_strjoin(var, replace);
//aaa$USER$PATHaasd
				//sma$USER
				//replace
			}
			else 
				return?
			//var + 1 ~ NULL env
		}
		else
			i++;
	}
	//split equals 합쳐
			//sma=ar$USER
}