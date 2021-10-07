/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:16:03 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:50:01 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"
# include "AST.h"
# include "list.h"
# include "utils.h"
# include "libft.h"

typedef struct s_io_modifier
{
	enum
	{
		REDIRECT_OUTPUT,
		REDIRECT_OUTPUT_APPEND,
		REDIRECT_INPUT,
		REDIRECT_INPUT_OUTPUT,
		REDIRECT_INPUT_OUTPUT_APPEND
	}			e_type;
	char		*infile;
	t_array		*out;
	int			fds[2];
	int			hd_flag;
}				t_io_mod;

typedef struct s_cmd
{
	int			proc_idx;
	char		*cmd;
	t_array		*argv;
	t_io_mod	*io_mod;
	t_list		*hd;
	int			save_out;
	int			save_in;
}				t_cmd;

typedef struct s_parser
{
	int			flag;
	int			hd_err;
	t_tokenizer	*t;
	t_token		*token;
	t_array		*var;
}				t_parser;

t_parser	*init_parser(char *str);
t_token		*eat(t_parser *p, int type);
int			parse_word(t_parser *p, t_ast *ast);
int			parse(t_parser *p, t_ast **ast);
t_ast		*parse_pipe(t_parser *p, t_ast *ast);
t_cmd		*init_cmd(char *value);
t_io_mod	*init_io_mod(int type);
void		parse_redirections(t_parser *p, t_ast *ast);
void		parse_double_quotes(t_parser *p, t_ast *ast);
void		parse_single_quotes(t_parser *p, t_ast *ast);
void		eat_words(t_parser *p, t_cmd *cmd);
char		*parse_str(char *str, t_array *var);
void		parse_env_var(t_parser *p, t_ast *ast);
void		parse_heredoc(t_parser *p, t_ast *ast);
#endif
