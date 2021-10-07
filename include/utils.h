/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:16:13 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 12:09:36 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "list.h"

typedef struct s_quote	t_quote;

struct s_quote
{
	int		type;
	int		other;
	int		open;
	int		con;
	int		len;
	int		close;
	char	*val;
};

char	*ft_strjoin_sep(char const *s1, char const *s2, int c);
char	*get_env_v(char *key, t_array *var);
void	print_error(char *str, char *arg);
void	hook(void);
void	free_tab(char **tab);
void	togle_open_close(t_quote *q, int o, int c);
#endif
