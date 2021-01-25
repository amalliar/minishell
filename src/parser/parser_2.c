/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:23:15 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 15:34:17 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			proc_ps_get_name(t_parser *parser)
{
	t_command	*cmd;

	cmd = (t_command *)parser->cmd_current->content;
	if (parser->tok_current->type == TT_WORD)
	{
		if (!((cmd->name = get_full_name(parser->tok_current->data))))
			exit_failure(MSH_VERSION": %s\n", strerror(errno));
		cmd->params = alloc_params_list(parser->tok_current);
		if (!(((cmd->params)[parser->params_idx++] = \
			ft_strdup(parser->tok_current->data))))
			exit_failure(MSH_VERSION": %s\n", strerror(errno));
		parser->state = PS_GET_PARAMS;
	}
	else if (parser->tok_current->type == TT_LEFT_AB)
		parser->state = PS_GET_STDIN;
	else if (parser->tok_current->type == TT_RIGHT_AB)
		parser->state = PS_GET_STDOUT;
	else if (parser->tok_current->type == TT_RIGHT_DAB)
		parser->state = PS_GET_STDOUT_APPEND;
	else if (parser->tok_current->type == TT_PIPE)
		parser->state = PS_PARSE_ERROR;
}

static void		proc_pipe(t_parser *parser)
{
	if (parser->tok_current->next->type == TT_NULL)
	{
		parser->state = PS_PARSE_ERROR;
		return ;
	}
	((t_command *)parser->cmd_current->content)->pipe = 1;
	parser->cmd_current->next = alloc_new_command();
	parser->cmd_current = parser->cmd_current->next;
	parser->state = PS_GET_NAME;
	parser->params_idx = 0;
}

void			proc_ps_get_params(t_parser *parser)
{
	t_command	*cmd;

	cmd = (t_command *)parser->cmd_current->content;
	if (parser->tok_current->type == TT_WORD)
	{
		if (!((cmd->params)[parser->params_idx++] = \
			ft_strdup(parser->tok_current->data)))
			exit_failure(MSH_VERSION": %s\n", strerror(errno));
	}
	else if (parser->tok_current->type == TT_LEFT_AB)
		parser->state = PS_GET_STDIN;
	else if (parser->tok_current->type == TT_RIGHT_AB)
		parser->state = PS_GET_STDOUT;
	else if (parser->tok_current->type == TT_RIGHT_DAB)
		parser->state = PS_GET_STDOUT_APPEND;
	else if (parser->tok_current->type == TT_PIPE)
		proc_pipe(parser);
}

void			proc_ps_get_stdin(t_parser *parser)
{
	t_command	*cmd;

	cmd = (t_command *)parser->cmd_current->content;
	if (parser->tok_current->type == TT_WORD)
	{
		cmd->f_stdin = 1;
		if (cmd->new_stdin != NULL)
			free(cmd->new_stdin);
		if (!(cmd->new_stdin = ft_strdup(parser->tok_current->data)))
			exit_failure(MSH_VERSION": %s\n", strerror(errno));
		if (cmd->name == NULL)
			parser->state = PS_GET_NAME;
		else
			parser->state = PS_GET_PARAMS;
	}
	else
		parser->state = PS_PARSE_ERROR;
}
