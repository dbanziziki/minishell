#include "tokenizer.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    t_tokenizer *t;
    int         ret;
    t_token     *token;

    t = init("\"hello there cat $USER\" | grep hello");
    token = get_next_token(t);
    printf("token value: %s\n", token->value);
    free(token->value);
    free(token);
    token = get_next_token(t);
    printf("token value: %s\n", token->value);
    free(token->value);
    free(token);
    token = get_next_token(t);
    printf("token value: %s\n", token->value);
    free(token->value);
    free(token);
    token = get_next_token(t);
    printf("token value: %s\n", token->value);
    free(token->value);
    free(token);
    /*token = get_next_token(t);
    printf("token value: %s\n", token->value);
    free(token->value);
    free(token);*/
    free(t);
    return 0;
}
