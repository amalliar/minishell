/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:35:48 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 18:35:52 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			proc_ps_get_stdout(t_parser *parser)
{
	t_command	*cmd;

	cmd = (t_command *)parser->cmd_current->content;
	if (parser->tok_current->type == TT_WORD)
	{
		cmd->f_stdout = 1;
		cmd->f_stdout_append = 0;
		if (cmd->new_stdout != NULL)
			free(cmd->new_stdout);
		if (!(cmd->new_stdout = ft_strdup(parser->tok_current->data)))
			exit_failure(MSH_VERSION": %s\n", strerror(errno));
		if (touch_new_stdout(cmd) != 0)
		{
			parser_clear(&parser->cmd_list);
			parser->state = PS_RETURN_RES;
			return ;
		}
		parser->state = (cmd->name == NULL) ? PS_GET_NAME : PS_GET_PARAMS;
	}
	else
		parser->state = PS_PARSE_ERROR;
}

/*
** Old stdout takes precedence over the new one if identical.
*/

static int		int_proc_ps_get_stdout_append(t_parser *parser)
{
	t_command	*cmd;

	cmd = (t_command *)parser->cmd_current->content;
	if (!(cmd->f_stdout && \
		!ft_strcmp(cmd->new_stdout, parser->tok_current->data)))
	{
		cmd->f_stdout = 0;
		cmd->f_stdout_append = 1;
		if (cmd->new_stdout != NULL)
			free(cmd->new_stdout);
		if (!(cmd->new_stdout = ft_strdup(parser->tok_current->data)))
			exit_failure(MSH_VERSION": %s\n", strerror(errno));
		if (touch_new_stdout(cmd) != 0)
		{
			parser_clear(&parser->cmd_list);
			parser->state = PS_RETURN_RES;
			return (1);
		}
	}
	return (0);
}

void			proc_ps_get_stdout_append(t_parser *parser)
{
	t_command	*cmd;

	cmd = (t_command *)parser->cmd_current->content;
	if (parser->tok_current->type == TT_WORD)
	{
		if (int_proc_ps_get_stdout_append(parser))
			return ;
		parser->state = (cmd->name == NULL) ? PS_GET_NAME : PS_GET_PARAMS;
	}
	else
		parser->state = PS_PARSE_ERROR;
}
