char	*ft_replace(t_data *data, char *str)
{//히니의 string이 들어오면, split하고 replace해서 다시 reunion해서 char *를 뱉는 함수

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
		if (!ft_strncmp(data->env[i], str, ft_strlen(str)))
		{
			free(str);
			str = ft_strdup(data->env[i] + j + 1);
			return (str);
		}
		j = 0;
		i++;
	}
	return (NULL);
}