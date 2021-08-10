/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:11:59 by sma               #+#    #+#             */
/*   Updated: 2021/07/04 16:35:35 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef	struct		s_data
{
	char			**cmd;
	char			*path;
	int				count;
}					t_data;

void				run_cmd(char **argv, char **envp, t_data *data);
int					redirect_in(char *file);
int					redirect_out(char *file);
void				pipe_connect(int fd[2], int f);
char				*path_join(char **envir, char *cmd);
char				**get_path(char **envp);
void				split_free(char **array);

#endif
