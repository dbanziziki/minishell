#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct p {
  int i;
}t_p;

int main(int argc, char const *argv[])
{
    t_list *list;
    int     i;
    t_p     *pl;
    t_p     *pl1;
    list = init_list(sizeof(t_p *));
    pl = malloc(sizeof(t_p));
    pl1 = malloc(sizeof(t_p));
    pl->i = 5;
    pl1->i = 10;
    list_push(list, pl);
    list_push(list, pl1);
    i = -1;
    while (++i < list->size)
    {
        printf("%d\n", ((t_p *)(list->items[i]))->i);
    }
    i = -1;
    while (++i < list->size)
        free(list->items[i]);
    free(list->items);
    free(list);
    return 0;
}