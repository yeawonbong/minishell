/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:37:42 by ybong             #+#    #+#             */
/*   Updated: 2021/09/26 15:24:32 by sma              ###   ########.fr       */
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
	int		stdio[2];
	int		fd[2];
}				t_data;

typedef struct s_var
{
	char	*modified;
	char	*var;
	char	*newbuf;
	int		i;
}				t_var;

typedef struct s_qte
{
	char	*modified;
	char	*inqte;
	char	*newbuf;
	int		i;
	int		qidx;
	char	quote;
}				t_qte;

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
	char	**space;
	char	*parse;
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
	int		u;
	int		t;
}				t_unset;

/*
** minishell.c
*/
void	get_cmd_arg(t_data *data, int idx);
void	get_cmd_path(t_data *data);
int		exec_in_child(t_data *data);
char	**ft_split_with(char c, char *buf, char **arr, t_data *data);

/*
**	ms_utils.c
*/
void	ft_split_free(char **strarr);
int		longer_len(char *str, char *str2);
int		ft_strarr_height(char **env);
char	*ft_join_free_all(char *str1, char *str2);
void	child_exec(t_data *data);

/*
** ms_fill_data.c
*/
char	*cmds_err(t_data *data, char *buf);
void	if_pipe_dup2(t_data *data, int fd1, int fd2, int toclose);
void	ft_filldata(t_data *data, char **envp);
int		non_redirect(t_data *data);

/*
**  ms_modify_buf (quote, envar)
*/
char	*ft_modify_buf(t_data *data, char *buf);
char	*ft_replace_var(t_data *data, char *var);
void	ft_envar_process(t_data *data, t_var *var);
char	*ft_modify_envar(t_data *data, t_var *var, char *buf);

/*
**	builtins
*/
int		check_builtin(char *buf);
void	ft_builtins(t_data *data);
void	ft_exit(t_data *data);
void	ft_export(t_data *data, int child);
void	ft_unset(t_data *data);
void	ft_cd(t_data *data);
void	ft_env(t_data *data);
void	ft_copy_env(char **src, char **dest);
void	ft_sort_env(t_data *data);
char	*ft_pwd(void);
void	ft_echo(char **cmd);

/*
**	redirect
*/
char	*ft_strjoin_free(char *dest, char *src);
int		redirect(t_data *data, int idx);
int		get_redirect(char *cmds, t_re *re);
char	*parse_redir(char *cmds);
void	close_dup_fd(int fd[2]);
int		child_in_buf(int re_fd[2], char *buf, int fd, char *str);
void	get_buf(int re_fd[2], char *buf, int fd, char *str);
int		check_redir(char *temp);
void	join_cmds(t_data *data, int idx);
int		re_exec_err(t_re *re);
int		redir_1(t_data *data, char *file);
int		redir_2(t_data *data, char *file);
int		redir_3(t_data *data, char *file);
int		redir_4(char *str, t_data *data);

/*
**	signal
*/
void	sig_set(int i);
void	sigint_handler(int signo);
void	child_handler(int signo);
void	redirect_handler(int signo);
int	check_redir(char *temp);
void	split_free(char **array);

#endif