#include "minishell.h"

static	int	ro_open_fd(char *file_name, int mode)
{
	int	fd;

	fd = open(file_name, mode | O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

static int	create_files(char **files, size_t size, int type)
{
	size_t	i;
	int		fd;

	i = -1;
	if (size == 0)
		return (0);
	while (++i < size - 1)
	{
		if (type == REDIRECT_OUTPUT)
			fd = ro_open_fd(files[i], O_TRUNC);
		else
			fd = ro_open_fd(files[i], O_APPEND);
		if (close(fd) < 0)
			return (-1);
	}
	return (0);
}

int	redirect_output(t_cmd *cmd)
{
	t_io_mod	*io_mod;
	int			i;
	size_t		out_size;

	i = -1;
	io_mod = cmd->io_mod;
	out_size = io_mod->out->size;
	if (create_files((char **)io_mod->out->items, out_size, io_mod->e_type) == -1)
		return (-1);
	if (io_mod->e_type == REDIRECT_OUTPUT
		|| io_mod->e_type == REDIRECT_INPUT_OUTPUT)
		io_mod->fds[1] = ro_open_fd(io_mod->out->items[out_size - 1], O_TRUNC);
	else
		io_mod->fds[1] = ro_open_fd(io_mod->out->items[out_size - 1], O_APPEND);
	if (cmd->io_mod->fds[1] < 0)
		return (-1);
	cmd->save_out = dup(STDOUT_FILENO);
	dup2(io_mod->fds[1], STDOUT_FILENO);
	if (close(io_mod->fds[1]) == -1)
		return (-1);
	return (0);
}

static int	check_infile(t_cmd *cmd)
{
	t_io_mod	*io;
	int			fds[2];

	io = cmd->io_mod;
	if (io->out->items
		&& !ft_strcmp(io->infile, io->out->items[io->out->size - 1])
		&& io->e_type != REDIRECT_INPUT_OUTPUT_APPEND
		&& io->e_type != REDIRECT_OUTPUT_APPEND)
	{
		if (pipe(fds) == -1)
			return (-1);
		dup2(fds[0], STDIN_FILENO);
		if (close(fds[0]) == -1 || close(fds[1]) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int	redirect_input(t_cmd *cmd)
{
	t_io_mod	*io;

	io = cmd->io_mod;
	if (io->hd_flag)
		return (0);
	if (check_infile(cmd))
		return (0);
	cmd->io_mod->fds[0] = open(cmd->io_mod->infile, O_RDONLY);
	if (cmd->io_mod->fds[0] < 0)
	{
		ft_putstr_fd("minishell: no file or directory: ", STDERR_FILENO);
		ft_putstr_fd(cmd->io_mod->infile, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (-1);
	}
	dup2(cmd->io_mod->fds[0], STDIN_FILENO);
	if (close(cmd->io_mod->fds[0]) == -1)
		return (-1);
	return (0);
}
