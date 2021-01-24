/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 10:07:03 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/24 10:27:04 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_tools.h"

void			print_token_list(t_token *token_list)
{
	while (token_list)
	{
		ft_printf("[%s]", token_list->data);
		if (token_list->type == TT_PIPE)
			ft_printf("[%s]\n", "TT_PIPE");
		else if (token_list->type == TT_LEFT_AB)
			ft_printf("[%s]\n", "TT_LEFT_AB");
		else if (token_list->type == TT_RIGHT_AB)
			ft_printf("[%s]\n", "TT_RIGHT_AB");
		else if (token_list->type == TT_RIGHT_DAB)
			ft_printf("[%s]\n", "TT_RIGHT_DAB");
		else if (token_list->type == TT_WORD)
			ft_printf("[%s]\n", "TT_WORD");
		else if (token_list->type == TT_NULL)
			ft_printf("[%s]\n", "TT_NULL");
		token_list = token_list->next;
	}
}

static void		print_params(char **params)
{
	int		count;

	count = 0;
	while (*params)
		ft_printf("arg_%d [%s]\n", count++, *params++);
}

void			print_command_list(t_list *command_list)
{
	t_command		*cmd;
	int				cmd_idx;

	cmd_idx = 0;
	while (command_list)
	{
		cmd = command_list->content;
		if (!cmd_idx)
			ft_printf("-------------------- NEXT_BATCH --------------------\n");
		ft_printf("CMD_%d\n", cmd_idx++);
		(cmd->name) ? ft_printf("name [%s]\n", cmd->name) : 0;
		(cmd->params) ? print_params(cmd->params) : 0;
		(cmd->f_stdin) ? ft_printf("< [%s]\n", cmd->new_stdin) : 0;
		(cmd->f_stdout) ? ft_printf("> [%s]\n", cmd->new_stdout) : 0;
		(cmd->f_stdout_append) ? ft_printf(">> [%s]\n", cmd->new_stdout) : 0;
		(cmd->pipe) ? ft_printf("pipe\n") : 0;
		(command_list->next) ? ft_printf("\n") : ft_printf("\n\n");
		command_list = command_list->next;
	}
}
