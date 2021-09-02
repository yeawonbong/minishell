#include "minishell.h"

char	*ft_join_free(char *str1, char *str2)
{
	char	*temp;

	temp = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (temp);	
}

char	*ft_replace_var(t_data *data, char *var)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data->env[i])
	{//USER=hi
		while (data->env[i][j] && data->env[i][j] != '=')
			j++; // env에서 앞에 인자 범위 알아내기 (ex_ yb=ybong 이라면 yb까지 끊기 위한 것)
		if (!ft_strncmp(data->env[i], var, ft_strlen(var))) //같으면
			break;
		j = 0;
		i++;
	}
	free(var);
	if (data->env[i])
		return (ft_strdup(data->env[i] + j + 1));
	else
		return (ft_strdup(""));
}

// 호출부 - if (ft_strchr(buf, '$')) 환경변수 잇을 때만 들어오기. 
char	*ft_modify_buf(t_data *data, char *buf)
{
	char	*modified;
	char	*var;
	char	*newbuf;
	int	i;
	int	j;

	i = 0;
	j = 0;
	modified = ft_strdup("");
	newbuf = buf;
	while (ft_strchr(newbuf, '$'))
	{
		i = 0;
		while (*(newbuf + i) != '$')
			i++;
		modified = ft_join_free(modified, ft_substr(newbuf, 0, i)); // free해야함
		newbuf += i + 1; // $ 다음을 가리킨다. 
		if (*newbuf == '$') // $$
		{
			var = ft_strdup(ft_itoa(getpid()));
			newbuf++;
		}
		else
		{
			i = 0;
			while (ft_isdigit(*(newbuf + i)) || ft_isalpha(*(newbuf + i)))
				i++;
			if (i == 0)
				var = ft_strdup("$");
			else
			{
				var = ft_substr(newbuf, 0, i);
				var = ft_replace_var(data, var);
				newbuf += i; // 환경변수 다음으로 이동 
			}
		}
		printf("modified VAR = %s\n", var);
		modified = ft_join_free(modified, var);
	}
	newbuf = ft_strdup(newbuf);
	modified = ft_join_free(modified, newbuf);
	free(buf);
	return (modified);
}
