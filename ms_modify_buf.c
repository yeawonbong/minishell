#include "minishell.h"

// char	*ft_replace_var(t_data *data, char *var)
// {

// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (data->env[i])
// 	{
// 		while (data->env[i][j] && data->env[i][j] != '=')
// 			j++; // env에서 앞에 인자 범위 알아내기 (ex_ yb=ybong 이라면 yb까지 끊기 위한 것)
// 		if (!ft_strncmp(data->env[i], var, ft_strlen(var)))
// 		{
// 			free(var);
// 			var = ft_strdup(data->env[i] + j + 1);
// 			return (var);
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	return (NULL); //env에 환경변수가 없을 때 NULL 로 replace
// }

// char	*ft_get_var()
// {

// }




//호출 할 때 , if (ft_strchr(buf, '$')
char	*ft_replace_var(t_data *data, char *buf)
{
	char	*var;
	char	*newvar;
	char	*newbuf;
	int	i;
	int	j;

//asdasds$USERasd$
	i = 0;
	j = 0;

	var = ft_strchr(buf, '$') + 1;
	if (*var == '$') // $$
	{
		newvar = ft_strdup(ft_itoa(getpid()));
		newbuf = ft_strdup(var + 2);
		// else
		// {
		// 	newvar = ft_strdup("$");
		// 	newbuf = ft_strdup(var + 1);
		// }
	//끝내서 나가기. 
	}
	else
	{
		var++;
		while (ft_isdigit(*(var + i)) || ft_isalpha(*(var + i)))
			i++;
		if (i)
			var = ft_substr(var, 0, i);
		else
		{
			newvar = ft_strdup("$");
			newbuf = ft_strdup(var + 1);
		}
		newbuf = ft_strdup(buf + i);
		while (data->env[i])
		{//USER=hi
			while (data->env[i][j] && data->env[i][j] != '=')
				j++; // env에서 앞에 인자 범위 알아내기 (ex_ yb=ybong 이라면 yb까지 끊기 위한 것)
			if (!ft_strncmp(data->env[i], var, ft_strlen(var))) //같으면
			{
				free(var);
				newvar = ft_strdup(data->env[i] + j + 1);
			}
			j = 0;
			i++;
		}
		newvar = ft_strdup("");
	}
	free(buf);
	buf = ft_strjoin(newvar, newbuf);
	return (buf);
	// return (NULL); //env에 환경변수가 없을 때 NULL 로 replace
}

char	*ft_modify_buf(t_data *data, char *buf) // ft_tokenize; // ft_split_args
{
	char	*modified;
	char	*after_var;
	char	*var;
	char	*temp;
	int		i;

	if (ft_strchr(buf, '$'))
	{
		i = 0;
		while (*(buf + i) != '$')
			i++;
		modified = ft_substr(buf, 0, i);
			printf("1\n");

	}
	else // if (i == 0) // $가 없거나, 아니면 첫번째 자리가 $일 경우.
		modified = ft_strdup("");
printf("2\n");
	while (ft_strchr(buf, '$'))
	{
printf("3\n");
		after_var = ft_strchr(buf, '$') + 1;
		i = 0;
		while (ft_isdigit(*(after_var + i)) || ft_isalpha(*(after_var + i)))
			i++;
		if (i == 0)
			var = ft_strdup("$");
		else
		{
			var = ft_substr(after_var, 0, i);
			printf("HERE\n");
			temp = (ft_strjoin(modified, ft_replace_var(data, var)));
			free(modified);
			free(var);
			modified = temp;
			free(temp);
			after_var += i; // var 뒤로 감.
		}
		printf("3\n");

			// free(after_var);
		// replace all the variables
		free(buf);
		buf = ft_strjoin(temp, after_var);
	}
	printf("FINFIN\n");
	return (buf);
}



//히니의 string이 들어오면, $단위로 split하고 env에서 값 환경변수 값 찾아서 replace해서 다시 reunion해서 char *를 뱉는 함수
// char	*ft_modify_buf(t_data *data, char *buf) // ft_tokenize; // ft_split_args
// {
// 	char	*before_var;
// 	char	*after_var;
// 	char	*var;
// 	char	*temp;
// 	int		i;

// 	if (ft_strchr(buf, '$'))
// 	{
// 		i = 0;
// 		while (*(buf + i) != '$')
// 			i++;
// 		before_var = ft_substr(buf, 0, i);
// 	}
// 	if (i == 0)
// 		before_var = ft_strdup("");
// // $없으면 return (buf)
// 	while (ft_strchr(buf, '$')) 
// 	{
// printf("before_var = %s\n", before_var);
// 		after_var = ft_strchr(buf, '$') + 1;
// 		i = 0;
// 		while (ft_isdigit(*(after_var + i)) || ft_isalpha(*(after_var + i)))
// 			i++;
// 		if (i == 0)
// 			var = ft_strdup("$");
// 		else
// 		{
// 			var = ft_substr(after_var, 0, i);
// 			var = ft_replace_var(data, var);
// 			if (i)
// 				after_var += i);
// 			else
// 				after_var = ft_strdup("");
// 		}
// printf("origin_var = %s|\n", var);
// printf("after_var = %s|\n", after_var);
// 		temp = ft_strjoin(before_var, var);
// printf("join1 = %s\n", temp);
// printf("join2 = %s\n", buf);
// 		free(temp);
// 		free(var);
// 		// free(after_var);
// 	}// replace all the variables
// 	free(buf);
// 	buf = ft_strjoin(temp, after_var);
// 	printf("FINFIN\n");
// 	return (buf);
// }
