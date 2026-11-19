#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

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

        printf("You entered: %s", line);
    }

    free(line);

    return 0;
}
