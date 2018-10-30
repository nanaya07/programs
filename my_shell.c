#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//boolean
#include <stdbool.h>
//string functions
#include <string.h> 
//fork and wait
#include <sys/types.h>
#include <sys/wait.h>
//signal
#include <signal.h>

//for buffers
#define BUF_SIZ 1024
#define MAX_SIZ 200

pid_t pid = -1 ; //Global

// solution for last problem (stay here for reference)
bool parsing_input(char* in, char out [MAX_SIZ][BUF_SIZ], int* sz)
{
    int in_sz = strlen(in); //input str len
    int s = 0;  //out array len
    int word_len = 0; //a token len
    char word[BUF_SIZ]; //a token 

    for(int i = 0; i < in_sz; i++)
    {
        printf("parsing %c\n", in[i]);
        if(in[i] != ' ' && in[i] != '\0' && in[i] != '\n')
        {
            word[word_len] = in[i];
            printf("copy char: %c\n", word[word_len]);
            word_len++;
        }
        else
        {
            word[word_len] = '\0';
            strcpy(out[s], word);
            printf("A token: %s\n", word);
            printf("A copy token: %s\n", out[s]);
            word_len = 0;
            s++;
            word[word_len] = '\0';
        }
    }
    *sz = s;
    printf("token numbers: %d\n", s);
    return true;
}

//better version
bool better_parsing_input(char* in, char out [MAX_SIZ][BUF_SIZ], int* sz)
{
    int in_sz = strlen(in); //input str len
    int s = 0;  //out array len
    int word_len = 0; //a token len
    char word[BUF_SIZ]; //a token 
    bool getting = false; 
    /*new flag!!
     *for checking whitespace, 
     *true if creating tokens, 
     *false if keep whitespasing.
     */

    for(int i = 0; i < in_sz; i++)
    {
        //printf("parsing %c\n", in[i]);
        if(in[i] != ' ' && in[i] != '\0' && in[i] != '\n')
        {
            word[word_len] = in[i];
            //printf("copy char: %c\n", word[word_len]);
            word_len++;
            getting = true;
        }
        else
        {
            if(getting)
            {
                word[word_len] = '\0';
                strcpy(out[s], word);
                //printf("A token: %s\n", word);
                //printf("A copy token: %s\n", out[s]);
                word_len = 0;
                s++;
                word[word_len] = '\0';
            }
            getting = false;
        }
    }
    *sz = s;
    //printf("token numbers: %d\n", s);
    return true;
}

//processing input
bool processing_input(char tok [MAX_SIZ][BUF_SIZ], int sz)
{
    pid = fork();
    int status;

    //building args for execvp
    char * args [MAX_SIZ];
    for (int i = 0; i < sz; i++)
        args[i] = tok[i];    
    args[sz] = NULL;
    
    switch (pid)
    {
        case -1:    //error
            perror("fork error");
            exit(0);
            break;
        case 0:     //child
            //printf("Hello from Child!\n");
            if(execvp(args[0], args) == -1)
                perror("exec error");
            break;
        default:    //parent
            //printf("Hello from Parent!\n");
            //printf("I wait Child(%d)\n", pid);
            wait(&status);
            //printf("Child is exit (%d)\n", status);
    }

    return pid >- 1 ? true:false;
}

//signal handler
void signal_handler(int sig) 
{
    printf("Caught signal %d\n", sig);
    switch(sig)
    {
        case SIGINT:
            printf("Killing child\n");
            kill(pid,SIGKILL);
            break;
        default:
            raise (sig);
    }
} 

int main()
{
    char buf [BUF_SIZ]; //buffer for user input
    char tokens [MAX_SIZ][BUF_SIZ]; //string array for tokens
    int size = 0;   //tokens array size

    //handling signals
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; /* Restart functions if
                                 interrupted by handler */
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("signal error\n");

    while (true)
    {
        //getting input
        printf("my_shell$ ");
        if(fgets(buf, BUF_SIZ, stdin) == NULL)
            perror("fgets error\n");
        //printf("print fgets: %s", buf);

        //parsing string
        if(!better_parsing_input(buf, tokens, &size))
            perror("parsing error\n");
        //printf("token numbers: %d\n", size);
        //for(int i = 0; i < size; i++)
        //    printf("token: %s\n", tokens[i]);
        /////////////////////////////////////////////////new
        if(!processing_input(tokens, size))
            perror("processing error\n");
    }
}
