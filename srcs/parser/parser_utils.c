#include "parser.h"

void    eat_words(t_parser *p, t_cmd *cmd)
{
    t_token *token;

    token = NULL;
    while (p->token->type == WORD_TOKEN)
    {
        token = eat(p, WORD_TOKEN);
        if (!token)
            return ;
        list_push(cmd->argv, token->value);
        free(token);
        token = NULL;
    }
}
