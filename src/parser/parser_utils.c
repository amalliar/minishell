/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:17:52 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 20:36:19 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list			*alloc_new_command(void)
{
	t_command	*cmd;
	t_list		*elem;

	if (!(cmd = malloc(sizeof(t_command))))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	cmd->name = NULL;
	cmd->params = NULL;
	cmd->pipe = 0;
	cmd->f_stdin = 0;
	cmd->f_stdout = 0;
	cmd->f_stdout_append = 0;
	cmd->new_stdout = NULL;
	cmd->new_stdin = NULL;
	if (!(elem = ft_lstnew(cmd)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	return (elem);
}

char			**alloc_params_list(t_token *token_list)
{
	int		tt_word_count;
	char	**params;

	tt_word_count = 0;
	while (token_list->type != TT_NULL)
	{
		if (token_list->type == TT_WORD)
			++tt_word_count;
		token_list = token_list->next;
	}
	if (!(params = ft_calloc(tt_word_count + 1, sizeof(char *))))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	return (params);
}

char			*get_unexpected_token(int token_type)
{
	if (token_type == TT_LEFT_AB)
		return ("<");
	else if (token_type == TT_RIGHT_AB)
		return (">");
	else if (token_type == TT_RIGHT_DAB)
		return (">>");
	else if (token_type == TT_NULL)
		return ("newline");
	else if (token_type == TT_PIPE)
		return ("|");
	else
		return ("");
}

static void		cmd_destroy(void *cmd_)
{
	t_command	*cmd;

	if (!cmd_)
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
	free(cmd);
}

void			parser_clear(t_list **command_list)
{
	ft_lstclear(command_list, cmd_destroy);
}
