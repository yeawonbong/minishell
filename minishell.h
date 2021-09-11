/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:37:42 by ybong             #+#    #+#             */
/*   Updated: 2021/09/11 17:45:28 by ybong            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

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

# define BUFSIZE 2048

int			g_status;

typedef struct s_data
{
	char	**cmds;
	char	**cmd_args;
	int		idx;
	char	**env;
	int		env_height;
	int		*sort_env;
	char	*path;
	int		redirect_flag;
	int		pipe_flag;
	int		stdio[2];
	int		fd[2];
}				t_data;

typedef struct s_mod
{
	char	*modified;
	char	*var;
	char	*newbuf;
	int		i;
	int		j;
}				t_mod;

typedef struct s_utils
{
	char	*ret;
	char	*subs;
	char	*join;
	int		len;
	int		idx;
}				t_utils;

typedef struct s_re
{
	char	**re_file;
	char	*cmd_j;
	int		*re_type;
	int		re_argc;
	int		re_count;
}				t_re;

typedef struct s_unset
{
	char	**unset_arg;
	char	**tempenv;
	char	*var;
	int		i;
	int		j;
	int		k;
	int		t;
}				t_unset;
/*
** minishell.c
*/
void	get_cmd_path(t_data *data);
int		exec_in_child(t_data *data);

/*
** ms_fill_data.c
*/
void	ft_copy_env(char **src, char **dest);
void	ft_sort_env(t_data *data);
void	ft_filldata(t_data *data, char **envp);
void	if_pipe_dup2(t_data *data, int fd1, int fd2, int toclose);

/*
**  ms_modify_buf.c
*/
char	*ft_modify_buf(t_data *data, char *buf);
char	*ft_join_free_all(char *str1, char *str2);

/*
**	builtins
*/
int		check_builtin(char *buf);
void	ft_builtins(t_data *data);
void	ft_export(t_data *data, int child);
void	ft_unset(t_data *data);
void	ft_cd(t_data *data);
void	ft_env(t_data *data);
void	ft_copy_env(char **src, char **dest);
void	ft_sort_env(t_data *data);
char	*ft_pwd(void);
void	ft_echo(char *cmd);

/*
**	ms_utils.c
*/
void	ft_split_free(char **strarr);
int		longer_len(char *str, char *str2);
int		ft_strarr_height(char **env);
char	*parse_redir(char *cmds);
void	get_redirect(char *cmds, t_re *re);

/*
**	redirect
*/
char	*ft_strjoin_free(char *dest, char *src);
int	redirect(t_data *data, int idx);
void	get_redirect(char *cmds, t_re *re);
char	*parse_redir(char *cmds);
void	redir_1(char *file);
void	redir_2(char *file);
void	redir_3(char *file);
void	redir_4(char *str);

#endif