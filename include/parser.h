/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:13:09 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 12:25:38 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "msh.h"
#include "lexer.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "process.h"
#include "error_tools.h"
#include "other_tools.h"

enum			e_parser_states
{
	PS_GET_NAME,
	PS_GET_PARAMS,
	PS_GET_STDIN,
	PS_GET_STDOUT,
	PS_GET_STDOUT_APPEND,
	PS_PARSE_ERROR
};

t_list			*alloc_new_command(void);
t_list			*parser_proc(t_token *token_list);
char			*get_unexpected_token(int token_type);
char			**alloc_params_list(t_token *token_list);
void			parser_clear(t_list **command_list);
int				touch_old_stdout(t_command *cmd);

#endif
