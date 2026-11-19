#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

    char *argv[100];
    char *token;
    int argc;

    while (1)
    {
        printf("msh> ");
        fflush(stdout);

        length = getline(&line, &capacity, stdin);

        if (length == -1)
        {
            printf("\n");
            break;
        }

        argc = 0;

        token = strtok(line, " \t\n");

        while (token != NULL && argc < 99)
        {
            argv[argc] = token;
            argc++;

            token = strtok(NULL, " \t\n");
        }

        argv[argc] = NULL;

        if (argc == 0)
        {
            continue;
        }

        printf("Command: %s\n", argv[0]);

        for (int i = 0; i < argc; i++)
        {
            printf("argv[%d]: %s\n", i, argv[i]);
        }
    }

    free(line);

    return 0;
}
