#include "list.h"

t_list  *init_list(size_t item_size)
{
	t_list  *list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->item_size = item_size;
	list->items = 0;
	list->size = 0;
	return (list);
}

void    list_push(t_list *list, void *item)
{
	list->size++;
	if (!list->items)
		list->items = malloc(list->item_size * (list->size + 1));
	else
		list->items = realloc(list->items, ((list->size + 1) * list->item_size)); //TODO: code my own realloc
	list->items[list->size - 1] = item;
	list->items[list->size] = 0;
}