/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:20:14 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 13:20:14 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str, char *arg)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
