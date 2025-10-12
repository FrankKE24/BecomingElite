#include <sys/types.h>
#include <sys/wait.h>
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//function  declarations for builtin commands
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

//List of builtin commands followed by their corresponding functions
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins(){
    return sizeof(builtin_str)/sizeof(char);
}

//Builtin function implementations
int lsh_cd(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }
    else{
        if(chdir(args[1]) != 0){
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args){
    int i;
    printf("Morans LSH\n");
    printf("Type a programs names and arguments, and hit enter.\n");
    printf("The following are built in: \n");

    for ( i = 0; i < lsh_num_builtins(); i++)
    {
        printf(" %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs:");
    return 1;
    
}


//always returns 0, to terminate execution
int lsh_exit(char **args){
    return 0;
}


//always return 1 to continue execution
int lsh_launch(char **args){
    pid_t pid;
    int status;

    pid = fork();
    if(pid == 0){
        if(execvp(args[0], args) == -1){
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid < 0){
        perror("lsh");
    }
    else{
        do{
            waitpid(pid, &status, WUNTRACED);
        }
        while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}


//return 1 if the shell should continue runnning, 0 if it shiuld terminate
int lsh_execute(char **args){
    int i;
    if(args[0] == NULL){
        return 1;
    }

    for(i=0; i < lsh_num_builtins(); i++){
        if(strcmp(args[0], builtin_str[i]) == 0){
            return(*builtin_func[i])(args);
        }
    }

    return lsh_launch(args);
}

//read a line of input from stdin, return the line from stdin
char *lsh_read_line(void){
    #ifdef LSH_USE_STD_GETLINE
        char *line = NULL;
        ssize_t bufsize = 0;  //have getline allocate a buffer for us
        if(getline(&line, &bufsize, stdin) == -1){
            if(feof(stdin)){
                exit(EXIT_SUCCESS); //we received an EOF
            }
            else{
                perror("lsh: getline\n");
                exit(EXIT_FAILURE);
            }
        }
        return line;
    #else
    #define LSH_RL_BUFSIZE 1024
        int bufsize = LSH_RL_BUFSIZE;
        int position = 0;
        char *buffer = malloc(sizeof(char) * bufsize);
        int c;

        if(!buffer){
            fprintf(stderr, "lsh: allocation error\n");
            exit(EXIT_FAILURE);
        }

        while (1){
            getchar();

            if(c == EOF){
                exit(EXIT_SUCCESS);
            }
            else if(c == '\n'){
                buffer[position] = '\0';
                return buffer;
            }
            else{
                buffer[position] = c;
            }
            position++;

            //if we have exceeded the buffer, reallocate
            if(position >= bufsize){
                bufsize += LSH_RL_BUFSIZE;
                buffer = realloc(buffer, bufsize);
                if(!buffer){
                    fprintf(stderr, "lsh: allocation error!");
                    exit(EXIT_FAILURE);
                }
            }

        }
    #endif   

}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

//split a line into tokens(very naively), line The line, return null trminated array of tokens

char **lsh_split_line(char *line){
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;

    if(!tokens){
        fprintf(stderr, "lsh: allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;

        if(position >= bufsize){
            bufsize += LSH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens){
                free(tokens_backup);

                fprintf(stderr," lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

//brief  loop geting input and executing it
void lsh_loop(void){
    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    }
    while(status);
}

int main(int argc, char const *argv[])
{
    lsh_loop();

    return EXIT_SUCCESS;

}


/*LSH is a simple implementation of a shell in C, and it is the subject of a tutorial on my website. It demonstrates the basics of how a shell works. That is: read, parse, fork, exec, and wait. Since its purpose is demonstration (not feature completeness or even fitness for casual use), it has many limitations, including:

Commands must be on a single line.
Arguments must be separated by whitespace.
No quoting arguments or escaping whitespace.
No piping or redirection.
Only builtins are: cd, help, exit.*/