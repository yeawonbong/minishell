#include "minishell.h"

char	*ft_replace_var(t_data *data, char *var)
{

	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		while (data->env[i][j] && data->env[i][j] != '=')
			j++; // env에서 앞에 인자 범위 알아내기 (ex_ yb=ybong 이라면 yb까지 끊기 위한 것)
		if (!ft_strncmp(data->env[i], var, ft_strlen(var)))
		{
			free(var);
			var = ft_strdup(data->env[i] + j + 1);
			return (var);
		}
		j = 0;
		i++;
	}
	return (NULL); //env에 환경변수가 없을 때 NULL 로 replace
}

// char	*ft_get_var()
// {

// }


//히니의 string이 들어오면, $단위로 split하고 env에서 값 환경변수 값 찾아서 replace해서 다시 reunion해서 char *를 뱉는 함수
char	*ft_modify_buf(t_data *data, char *buf) // ft_tokenize; // ft_split_args
{
	char	*tojoin;
	char	*temp;
	char	*var;
	char	*p;
	int		i;

	i = 0;
	if (*buf != '$' && ft_strchr(buf, '$'))
	{
		while (*(buf + i) != '$')
			i++;
		tojoin = ft_substr(buf, 0, i);
	}//얘를 while 안으로 넣어야해 (8/16)
	else
		tojoin = ft_strdup("");
	while (ft_strchr(buf, '$'))
	{
		p = ft_strchr(buf, '$') + 1;
		i = 0;
		while (ft_isdigit(*(p + i)) || ft_isalpha(*(p + i)))
			i++;
		if (i == 0)
			var = ft_strdup("$");
		else
		{
			var = ft_substr(p, 0, i);
			var = ft_replace_var(data, var);
			p += i;
		}
		temp = ft_strjoin(var, p);
		free(var);
		free(buf);
		buf = temp;
		(printf("last buf = %s\n", buf));
	}// replace all the variables
	temp = ft_strjoin(tojoin, buf);
	free(tojoin);
	free(buf);
	buf = temp;
	return (buf);
}