/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 06:23:19 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 20:41:44 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		parser_check_error(t_parser *parser)
{
	if (parser->state != PS_GET_NAME && parser->state != PS_GET_PARAMS)
	{
		ft_printf(MSH_VERSION": syntax error near unexpected token `%s'\n", \
			get_unexpected_token(parser->tok_current->type));
		parser_clear(&parser->cmd_list);
	}
}

t_list			*parser_proc(t_token *token_list)
{
	t_parser	parser;

	if (token_list->type == TT_NULL)
		return (NULL);
	parser_init(&parser, token_list);
	while (parser.tok_current->type != TT_NULL)
	{
		if (parser.state == PS_GET_NAME)
			proc_ps_get_name(&parser);
		else if (parser.state == PS_GET_PARAMS)
			proc_ps_get_params(&parser);
		else if (parser.state == PS_GET_STDIN)
			proc_ps_get_stdin(&parser);
		else if (parser.state == PS_GET_STDOUT)
			proc_ps_get_stdout(&parser);
		else if (parser.state == PS_GET_STDOUT_APPEND)
			proc_ps_get_stdout_append(&parser);
		if (parser.state == PS_RETURN_RES)
			return (parser.cmd_list);
		if (parser.state == PS_PARSE_ERROR)
			break ;
		parser.tok_current = parser.tok_current->next;
	}
	parser_check_error(&parser);
	return (parser.cmd_list);
}
