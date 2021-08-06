#include "tokenizer.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    t_tokenizer *t;
    int         ret;
    t_token     *token;

    t = init("   cat grep");
    token = get_next_token(t);
    ret = has_more_tokens(t);
    printf("token value: %s\n", token->value);
    free(token->value);
    free(token);
    token = get_next_token(t);
    printf("token value: %s\n", token->value);
    free(token->value);
    free(token);
    ret = has_more_tokens(t);
    printf("cursor %lu len: %lu\n", t->cursor, t->len);
    free(t);
    return 0;
}
