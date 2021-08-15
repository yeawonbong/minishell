#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>

#define BUFSIZE 4000 //max_buf ? 

typedef	struct		s_data
{
	char	**cmds; //cmd 토큰 cat aa | grep a
	char	**cmd_args; // 토큰 cat . aa
	char	**env;
	int		env_height;
	int		*sort_env;
	char	*path;
	int		idx;
}					t_data;

/*
** minishell.c
*/


/*
** ms_fill_data.c
*/
void	ft_copy_env(char **src, char **dest);
void	ft_sort_env(t_data *data);
void	ft_filldata(t_data *data, char **envp); //이름수정할래

/*
**  ms_run_cmd.c
*/
void			run_cmd(char **envp, t_data *data);

/*
**	ms_export.c
*/
char	*ft_reunion(char **strarr, int strnum);
char	*ft_replace(t_data *data, char *var);
char	*ft_replace_envar(t_data *data, char *envar);
void	ft_export(t_data *data, char *buf);
void	ft_env(t_data *data, char *buf);

/*
**	ms_utils.c
*/
void	ft_split_free(char **strarr);
int		longer_len(char *str, char *str2);
int     ft_strarr_height(char **env);


#endif