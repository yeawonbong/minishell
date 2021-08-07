#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFSIZE 1024

/*
** minishell.c
*/

/*
** ms_builtins.c
*/
void	ft_echo(char *buf);
void	ft_cd(char *buf);
void	ft_pwd(void);



#endif