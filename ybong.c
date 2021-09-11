#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    char    *buf;

    while(1)
    {
        buf = readline("ybong$ ") ;
	    if (*buf)
		    add_history(buf);
        free(buf);
		signal(SIGINT, SIG_IGN);
    }
}