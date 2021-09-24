
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char    **add_str(char **arr, char *toadd);
char	**ft_split_with(char c, char *buf, char **arr);

int main(){
    int i=0;
    char **cmd;
    char *cmds[3] = {"start", 0};

    char *buf = "echo \"grep gggabc|cc\" | echo \"hihi|ls\"";

    cmd = cmds;
    cmd = ft_split_with('|', buf, cmd);
    // if(execve(cmd[0], cmd, 0) == -1)
    //     perror("error : ");
    // return (0);
    // cmd = add_str(cmd, "hello");
    while (cmd[i])
    {
        printf("cmmd = %s\n", cmd[i]);
        i++;
    }
    return (0);
}