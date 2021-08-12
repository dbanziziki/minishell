#include "parser.h"

static void parse_redirect_output(t_parser *p, t_cmd *cmd)
{
    t_token *token;

    /*TODO: chained redirection*/
    token = eat(p, GREATER_THAN_TOKEN);
    free(token->value);
    free(token);
    token = eat(p, WORD_TOKEN);
    cmd->io_mod = init_io_mod(NULL, token->value, REDIRECT_OUTPUT);
    free(token);
}

static void parse_redirect_output_append(t_parser *p, t_cmd *cmd)
{
    t_token *token;

    token = eat(p, GGREATER_THAN_TOKEN);
    free(token->value);
    free(token);
    token = eat(p, WORD_TOKEN);
    if (cmd->io_mod)
        cmd->io_mod->outfile = token->value;
    else
        cmd->io_mod = init_io_mod(NULL, token->value, REDIRECT_OUTPUT_APPEND);
    free(token);
}

static void parse_redirect_input(t_parser *p, t_cmd *cmd)
{
    t_token *token;

    token = eat(p, LESS_THAN_TOKEN);
    free(token->value);
    free(token);
    if (cmd->argv->size > 2) /*if we already have argv we skip the token*/
    {
        /*doesnt work for grep include < infile for ex*/
        token = eat(p, WORD_TOKEN);
        free(token->value);
        free(token);
    }
    else
    {
        token = eat(p, WORD_TOKEN);
        if (cmd->io_mod)
            cmd->io_mod->infile = token->value;
        else
            cmd->io_mod = init_io_mod(token->value, NULL, REDIRECT_INPUT);
        free(token);
    }
}

void		parse_redirection(t_parser *p, t_AST *ast)
{
    t_cmd   *cmd;
    t_AST   *last;

    last = ast;
    while (last->next)
        last = last->next;
    cmd = (t_cmd *)last->body;
    if (p->token->type == GREATER_THAN_TOKEN)
        parse_redirect_output(p, cmd);
    else if (p->token->type == LESS_THAN_TOKEN)
        parse_redirect_input(p, cmd);
    else if (p->token->type == GGREATER_THAN_TOKEN)
        parse_redirect_output_append(p, cmd);
}