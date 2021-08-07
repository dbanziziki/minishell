#ifndef LIST_H
# define LIST_H

#include <unistd.h>
#include <stdlib.h>

typedef struct s_list
{
    void    **items;
    size_t  size;
    size_t  item_size;
}               t_list;

t_list  *init_list(size_t item_size);
void    list_push(t_list *list, void *item);
#endif