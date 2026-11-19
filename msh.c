#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

    char *argv[100];
    char *token;
    int argc;

    pid_t pid;
    int status;
    int last_status = 0;
	

    while (1)
    {
        printf("msh[%d]> ", last_status);
        fflush(stdout);

        length = getline(&line, &capacity, stdin);

        if (length == -1)
        {
            printf("\n");
            break;
        }

        /* Parse the command */
        argc = 0;

        token = strtok(line, " \t\n");

        while (token != NULL && argc < 99)
        {
            argv[argc] = token;
            argc++;

            token = strtok(NULL, " \t\n");
        }

        argv[argc] = NULL;

        /* Ignore blank lines */
        if (argc == 0)
        {
            continue;
        }
/* Built-in: help */
if (strcmp(argv[0], "help") == 0)
{   
    last_status = 0;
    printf("Available built-in commands:\n");
    printf("  cd [dir]  - Change directory\n");
    printf("  help      - Display this help message\n");
    printf("  exit      - Exit the shell\n");

    continue;
}

/* Built-in: exit */
if (strcmp(argv[0], "exit") == 0)
{
    free(line);
    return 0;
}

/* Built-in: cd */
if (strcmp(argv[0], "cd") == 0)
{
    const char *directory;

    if (argv[1] == NULL)
    {
        directory = getenv("HOME");

        if (directory == NULL)
        {
            fprintf(stderr, "cd: HOME is not set\n");
            continue;
        }
    }
    else
    {
        directory = argv[1];
    }

    if (chdir(directory) == -1)
    {
        perror("cd");
	last_status = 1;
    }
    else
    {
	last_status = 0;
    }

    continue;
}



        /* Create a child process */
        pid = fork();

        if (pid < 0)
        {
            perror("fork");
            continue;
        }

        /* Child process */
        if (pid == 0)
        {
            execvp(argv[0], argv);

            /* Reached only if execvp fails */
            if (errno == ENOENT)
            {
                fprintf(stderr, "%s: command not found\n", argv[0]);
                _exit(127);
            }

            perror("execvp");
            _exit(126);
        }

        
        /* Parent process */
        

	else
    {
    pid_t result;

    do
    {
        result = waitpid(pid, &status, 0);
    }
    while (result == -1 && errno == EINTR);

    if (result == -1)
    {
        perror("waitpid");
        last_status = 1;
        continue;
    }

    if (WIFEXITED(status))
    {
        last_status = WEXITSTATUS(status);

        printf("Command exited with status: %d\n",
               last_status);
    }
    else if (WIFSIGNALED(status))
    {
        last_status = 128 + WTERMSIG(status);

        printf("Command terminated by signal: %d\n",
               WTERMSIG(status));

        printf("Exit status: %d\n", last_status);
    }
}


    }

    free(line);

    return 0;
}
