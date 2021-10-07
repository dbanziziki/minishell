/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:15:58 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:15:59 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_ast
{
	enum
	{
		PROGRAM,
		CMD_AND_ARG,
		PIPE_CMD_AND_ARG,
	}				e_type;
	void			*body;
	struct s_ast	*next;
	struct s_ast	*prev;
}					t_ast;

typedef struct s_program
{
	int			nb_pipes;
	int			has_pipes;
}				t_program;

t_ast		*init_ast(int type, void *body);
void		addback_ast(t_ast **ast, t_ast *new);
t_program	*init_prog(void);
void		print_ast(t_ast *ast);
t_ast		*get_last(t_ast **ast);
#endif
