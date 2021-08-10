/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:48:52 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:32:32 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	temp = new;
	lst = lst->next;
	while (lst)
	{
		temp->next = ft_lstnew(f(lst->content));
		if (!temp->next)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		temp = temp->next;
		lst = lst->next;
	}
	return (new);
}
