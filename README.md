# minishell (bash shell 구현)
The objective of this project is to create a simple shell.

직접 구현한 C표준 라이브러리를 사용하였습니다. 입력으로 명령을 받고, 쉘 프로그램 내장 명령(echo, cd, pwd, export, unset, env, exit)인 경우에는 본 프로세스에서 실행하고, 이외 경우에는 자식 프로세스로 분기하여 명령의 실행파일을 경로(환경변수의 PATH)에서 받아와 유효한 PATH를 찾아 자식 프로세스에서 실행합니다. 
환경변수, 리다이렉션과 ‘, “, 파이프 등의 옵션 모두 구현하고, 시그널에 따른 동작을 우회해주어 bash shell과 같게 동작하게 구현했습니다. 


# 실행방법
1. `make`  
2. `./minishell`
