/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:15:48 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:15:50 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_array
{
	void		**items;
	size_t		size;
	size_t		item_size;
}				t_array;

t_array	*init_list(size_t item_size);
void	list_push(t_array *list, void *item);

#endif
