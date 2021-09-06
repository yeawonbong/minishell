#include "../minishell.h"

int main(int argc, char **argv, char **envp){


char *lss[] = {"ls", NULL};
char *wcc[] = {"wc", NULL};
int stdio[2];
int fd[2];
char out[BUFSIZE];
// for (int i=0; *cmds[i]; i++)
//     printf("cmds = %s\n", cmds[i]);
stdio[0] = dup(STDIN_FILENO);
stdio[1] = dup(STDOUT_FILENO);

pipe(fd);
int pid = fork();
if (pid == 0)
{
    dup2(fd[1], STDOUT_FILENO);
    // dup2(fd[0], STDIN_FILENO);
printf("he");

    execve("/bin/ls", lss, envp);
}
wait(0);


    // dup2(fd[0], STDIN_FILENO);
    // dup2(fd[1], STDOUT_FILENO);
dup2(stdio[1], STDOUT_FILENO);

  pid = fork();  // dup2(fd[0], STDIN_FILENO);
  if (pid == 0)  
  {
    dup2(fd[1], STDOUT_FILENO);
    execve("usr/bin/wc", wcc, envp);  
  }
  wait(0);
    // ft_putstr_fd("hi", STDOUT_FILENO);
read(fd[0], out, BUFSIZE);
dup2(stdio[1], STDOUT_FILENO);
printf("OUT = %s\n", out);


}
