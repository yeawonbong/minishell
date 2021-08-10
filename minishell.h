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
	int		*sort_env;
	char	**cmds;
	char	**cmd_args;
	char	*path;
	int		idx;
}					t_data;

/*
** minishell.c
*/

/*
** ms_builtins.c
*/
void	ft_sort_env(char **envp, t_data *data);
void	ft_export(char **envp, t_data *data, char *buf);


/*
**  ms_run_cmd.c
*/
void			run_cmd(char **envp, t_data *data);


#endif