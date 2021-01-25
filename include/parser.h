/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:13:09 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 18:36:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <string.h>
# include <errno.h>
# include <fcntl.h>

# include "msh.h"
# include "lexer.h"
# include "ft_list.h"
# include "ft_stdio.h"
# include "ft_stdlib.h"
# include "ft_string.h"
# include "process.h"
# include "error_tools.h"
# include "other_tools.h"

enum			e_parser_states
{
	PS_GET_NAME,
	PS_GET_PARAMS,
	PS_GET_STDIN,
	PS_GET_STDOUT,
	PS_GET_STDOUT_APPEND,
	PS_PARSE_ERROR,
	PS_RETURN_RES
};

typedef struct	s_parser
{
	int			state;
	int			params_idx;
	t_list		*cmd_list;
	t_list		*cmd_current;
	t_token		*tok_current;
}				t_parser;

t_list			*alloc_new_command(void);
t_list			*parser_proc(t_token *token_list);
char			*get_unexpected_token(int token_type);
char			**alloc_params_list(t_token *token_list);
void			parser_init(t_parser *parser, t_token *token_list);
void			parser_clear(t_list **command_list);
void			proc_ps_get_name(t_parser *parser);
void			proc_ps_get_params(t_parser *parser);
void			proc_ps_get_stdin(t_parser *parser);
void			proc_ps_get_stdout(t_parser *parser);
void			proc_ps_get_stdout_append(t_parser *parser);
int				touch_new_stdout(t_command *cmd);

#endif
