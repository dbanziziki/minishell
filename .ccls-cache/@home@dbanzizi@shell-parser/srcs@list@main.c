#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

int main(int argc, char const *argv[])
{
	t_list *list;
	int 	i;

	list = init_list(sizeof(char *));
	list_push(list, strdup("Hello"));
	list_push(list, strdup("Hello"));
	list_push(list, strdup("Hello"));
	printf("size: [%ld]\n", list->size);
	while (++i < list->size)
		free(list->items[i]);
	free(list->items);
	free(list);
	return 0;
}