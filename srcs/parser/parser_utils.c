#include "parser.h"

void    eat_words(t_parser *p, t_cmd *cmd)
{
    t_token *token;

    token = NULL;
    while (p->token->type == WORD_TOKEN)
    {
        token = eat(p, WORD_TOKEN);
        list_push(cmd->argv, token->value);
        free(token);
        token = NULL;
    }
}

t_heredoc   *init_heredoc(char *delimiter)
{
    t_heredoc   *hd;

    hd = (t_heredoc *)malloc(sizeof(t_heredoc));
    if (!hd) 
        return (NULL);
    hd->delimiter = delimiter;
    hd->cmd = NULL;
    return (hd);
}
