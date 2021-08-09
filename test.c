#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    char *new_argv[] = {"cat", "test.c", NULL};

    pid = fork();
    if (pid == 0)
    {
        printf("child process\n");
        execvp("cat", new_argv);
    }
    printf("parent process\n");
    return 0;
}
