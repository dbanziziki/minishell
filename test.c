#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	pid_t	pid;
	char	*new_argv[] = {"ls", "-l", NULL};
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open(argv[1], O_TRUNC | O_CREAT | O_WRONLY, 0777);
		printf("child process\n");
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execvp("ls", new_argv);
	}
	printf("parent process\n");
	return 0;
}
