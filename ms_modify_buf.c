#include "minishell.h"

char	*ft_join_free_all(char *str1, char *str2)
{
	char	*temp;

	temp = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (temp);
}

char	*ft_replace_var(t_data *data, char *var)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		while (data->env[i][j] && data->env[i][j] != '=')
			j++;
		if (!ft_strncmp(data->env[i], var, ft_strlen(var)))
			break ;
		j = 0;
		i++;
	}
	free(var);
	if (data->env[i])
		return (ft_strdup(data->env[i] + j + 1));
	else
		return (ft_strdup(""));
}

void	ft_modify_process(t_data *data, t_mod *mod)
{
	if (*mod->newbuf == '$')
	{
		mod->var = ft_strdup(ft_itoa(getpid())); //getpid 뺴주기
		mod->newbuf++;
	}
	else
	{
		mod->i = 0;
		while (ft_isdigit(*(mod->newbuf + mod->i)) \
		|| ft_isalpha(*(mod->newbuf + mod->i)))
			mod->i++;
		if (mod->i == 0)
			mod->var = ft_strdup("$");
		else
		{
			mod->var = ft_substr(mod->newbuf, 0, mod->i);
			mod->var = ft_replace_var(data, mod->var);
			mod->newbuf += mod->i;
		}
	}
	mod->modified = ft_join_free_all(mod->modified, mod->var);
}

char	*ft_modify_buf(t_data *data, char *buf)
{
	t_mod	mod;

	mod.i = 0;
	mod.j = 0;
	mod.modified = ft_strdup("");
	mod.newbuf = buf;
	while (ft_strchr(mod.newbuf, '$'))
	{
		mod.i = 0;
		while (*(mod.newbuf + mod.i) != '$')
			mod.i++;
		mod.modified = ft_join_free_all(mod.modified, \
							ft_substr(mod.newbuf, 0, mod.i));
		mod.newbuf += mod.i + 1;
		ft_modify_process(data, &mod);
	}
	mod.newbuf = ft_strdup(mod.newbuf);
	mod.modified = ft_join_free_all(mod.modified, mod.newbuf);
	free(buf);
	return (mod.modified);
}
