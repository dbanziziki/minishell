/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 12:35:40 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/31 11:16:49 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	save_buffer(char **file, char *buffer, int ret)
{
	char	*temp_content;

	buffer[ret] = '\0';
	temp_content = 0;
	if (*file == NULL)
	{
		temp_content = ft_strndup(buffer, ret);
		if (!temp_content)
			return (-1);
	}
	else
	{
		temp_content = ft_strjoin(*file, buffer);
		if (!temp_content)
			return (-1);
		free(*file);
	}
	*file = temp_content;
	if (ft_strchr(*file, '\n'))
		return (1);
	return (0);
}

static int	ft_cpy_line(char **src, char **line, int len)
{
	char	*temp1;

	if (!src || !(*src))
		return (0);
	*line = ft_strndup(*src, len);
	if (!(*line))
		return (-1);
	temp1 = ft_strndup(*src + (len + 1), ft_strlen(*src + (len + 1)));
	if (!temp1)
		return (-1);
	free(*src);
	*src = temp1;
	return (1);
}

static int	extract_line(char **src, char **line)
{
	size_t	len;

	if (!src || !(*src))
		return (0);
	len = 0;
	while ((*src)[len] && (*src)[len] != '\n')
		len++;
	if ((*src)[len] == '\n')
		return (ft_cpy_line(src, line, len));
	*line = *src;
	*src = 0;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*file[OPEN_MAX];
	int			ret;
	int			err;

	if ((fd < 0 || line == NULL || fd >= OPEN_MAX || BUFFER_SIZE <= 0))
		return (-1);
	if (ft_strchr(file[fd], '\n'))
		return (extract_line(&file[fd], line));
	ret = read(fd, buffer, BUFFER_SIZE);
	while (ret >= 0)
	{
		err = save_buffer(&file[fd], buffer, ret);
		if (err == 1 || ret == 0)
			break ;
		if (err < 0)
			return (-1);
		ret = read(fd, buffer, BUFFER_SIZE);
	}
	if (ret < 0)
		return (-1);
	return (extract_line(&file[fd], line));
}
