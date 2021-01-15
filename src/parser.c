/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 06:23:19 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/15 06:43:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "process.h"
#include "other_tools.h"
#include "lexer.h"

t_list			*parser_proc(t_token *token_list)
{
	return (NULL);
}

void			cmd_destroy(void *cmd_)
{
	t_command	*cmd;

	if (!cmd)
		return ;
	cmd = cmd_;
	if (cmd->name)
		free(cmd->name);
	if (cmd->params)
		strarr_free(cmd->params);
	if (cmd->new_stdout)
		free(cmd->new_stdout);
	if (cmd->new_stdin)
		free(cmd->new_stdin);
		
}

void			parser_clear(t_list **command_list)
{
	if (command_list && *command_list)
	{
		ft_lstclear(command_list, cmd_destroy);
		*command_list = NULL;
	}
}
