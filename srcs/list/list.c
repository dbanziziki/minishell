#include "list.h"

t_array	*init_list(size_t item_size)
{
	t_array	*list;

	list = (t_array *)malloc(sizeof(t_array));
	if (!list)
		return (NULL);
	list->item_size = item_size;
	list->items = NULL;
	list->size = 0;
	return (list);
}

void	list_push(t_array *list, void *item)
{
	size_t	old_size;
	size_t	new_size;

	old_size = (list->size) * list->item_size;
	list->size++;
	new_size = (list->size + 1) * list->item_size;
	if (!list->items)
		list->items = malloc(list->item_size * (list->size + 1));
	else
		list->items = ft_realloc(list->items, new_size, old_size);
	list->items[list->size - 1] = item;
	list->items[list->size] = 0;
}
