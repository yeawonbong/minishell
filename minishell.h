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






#define BUFSIZE 2048 //max_buf ? 

typedef	struct		s_data
{
	char	**cmds;
	char	**cmd_args;
	char	**env;
	int		env_height;
	int		*sort_env;
	char	*path;
	int		idx;
}					t_data;

/*
** minishell.c
*/
int     ft_env_height(char **env);
void	ft_copy_env(char **src, char **dest);
void	ft_filldata(t_data *data, char **envp);


/*
** ms_builtins.c
*/
void	ft_sort_env(t_data *data);
void	ft_export(t_data *data, char *buf);


/*
**  ms_run_cmd.c
*/
void			run_cmd(char **envp, t_data *data);


#endif