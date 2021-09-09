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
# include <signal.h>
# include <errno.h>
# include <string.h>

#define BUFSIZE 4000 //max_buf ? 

typedef	struct	s_data
{
	char	**cmds; //cmd 토큰 cat aa | grep a
	char	**cmd_args; // 토큰 cat . aa
	char	**env;
	int		env_height;
	int		*sort_env;
	char	*path;
	int		idx; //cmd의 idx
	int		stdio[2];
	int		redirect_flag;
	int		pipe_flag;
	int		fd[2];
}				t_data;

typedef struct	s_mod
{
	char	*modified;
	char	*var;
	char*	newbuf;
	int		i;
	int		j;
}				t_mod;

typedef struct	s_utils
{
	char	*ret;
	char	*subs;
	char	*join;
	int		len;
	int		idx;
}				t_utils;

typedef struct	s_re
{
	char	**re_file;
	char	*cmd_j;
	int		*re_type;
	int		re_argc;
	int		re_count;
}				t_re;

// typedef struct s_fd
// {
// 	int	stdin_origin;
// 	int	stdout_origin;
// }



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
**  ms_modify_buf.c
*/
char	*ft_replace_var(t_data *data, char *var);
char	*ft_modify_buf(t_data *data, char *buf);

/*
**	ms_env.c
*/
void	ft_env(t_data *data);
void	ft_copy_env(char **src, char **dest);
void	ft_sort_env(t_data *data);


void			get_cmd_path(t_data *data);

/*
**	ms_export.c
*/
void	ft_export(t_data *data, int child);
void	ft_unset(t_data *data, char *buf);

/*
**	ms_utils.c
*/
void	ft_split_free(char **strarr);
int		longer_len(char *str, char *str2);
int     ft_strarr_height(char **env);
char*	parse_redir(char *cmds);
void	get_redirect(char *cmds, t_re *re);
void	ft_cd(t_data *data);
char	*get_cwd(void);

/*
**	redirect
*/
void	redirect(t_data *data, int idx);
char	*parse_redir(char *cmds);
void	get_redirect(char *cmds, t_re *re);
void	redir_1(char *file);
void	redir_2(char *file);
void	redir_3(char *file);
void	redir_4(char *str);
char	*ft_strjoin_free(char *dest, char *src);




int check_builtin(char *buf);
void	ft_builtins(t_data *data);

#endif