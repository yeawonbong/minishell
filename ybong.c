#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

void sigint_handler(int signo)
{
	printf("Ctrl_C\n");
}

int main(){
	char    *buf;


	while(1)
	{
		// buf = readline("ybong$ ") ;
		// if (*buf)
		// 	add_history(buf);
		// free(buf);
		// while(1){
		signal(SIGINT, sigint_handler);
		// }
	}
}
