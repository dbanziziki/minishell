#include "minishell.h"

static	int ro_open_fd(char *file_name, int mode)
{
	int	fd;

	fd = open(file_name, mode | O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	redirect_output(t_cmd *cmd)
{
	t_io_mod	*io_mod;
	int			i;
	int			out_size;

	i = -1;
	io_mod = cmd->io_mod;
	out_size = io_mod->out->size;
	while (++i < io_mod->out->size - 1)
	{
		if (io_mod->type == REDIRECT_OUTPUT)
			io_mod->fds[1] = ro_open_fd(io_mod->out->items[i], O_TRUNC);
		else
			io_mod->fds[1] = ro_open_fd(io_mod->out->items[i], O_APPEND);
		if (close(io_mod->fds[1]) < 0)
			return (-1);
	}
	if (io_mod->type == REDIRECT_OUTPUT)
		io_mod->fds[1] = ro_open_fd(io_mod->out->items[out_size - 1], O_TRUNC);
	else
		io_mod->fds[1] = ro_open_fd(io_mod->out->items[out_size - 1], O_APPEND);
	if (cmd->io_mod->fds[1] < 0)
		return (-1);
	dup2(io_mod->fds[1], STDOUT_FILENO);
	if (close(io_mod->fds[1]) == -1)
		return (-1);
	return (0);
}

int	redirect_input(t_cmd *cmd)
{
	t_io_mod	*io;

	io = cmd->io_mod;
	cmd->io_mod->fds[0] = open(cmd->io_mod->infile, O_RDONLY);
	if (cmd->io_mod->fds[0] < 0)
	{
		printf("minishell: no file or directory: %s\n", cmd->io_mod->infile);
		return (-1);
	}
	dup2(cmd->io_mod->fds[0], STDIN_FILENO);
	if (close(cmd->io_mod->fds[0]) == -1)
		return (1);
	return (0);
}
