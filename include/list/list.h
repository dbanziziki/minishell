#ifndef LIST_H
# define LIST_H

#include <unistd.h>
#include <stdlib.h>


typedef struct s_array
{
    void    **items;
    size_t  size;
    size_t  item_size;
}               t_array;

t_array  *init_list(size_t item_size);
void    list_push(t_array *list, void *item);

#endif