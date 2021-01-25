/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 06:23:19 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 13:03:30 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list			*parser_proc(t_token *token_list)
{
	t_list		*cmd_list;
	t_list		*cmd_current;
	int			parser_state;
	int			params_idx;

	if (token_list->type == TT_NULL)
		return (NULL);
	cmd_list = alloc_new_command();
	cmd_current = cmd_list;
	parser_state = PS_GET_NAME;
	params_idx = 0;
	while (token_list->type != TT_NULL)
	{
		if (parser_state == PS_GET_NAME)
		{
			if (token_list->type == TT_WORD)
			{
				if (!(((t_command *)cmd_current->content)->name = get_full_name(token_list->data)))
					exit_failure(MSH_VERSION": %s\n", strerror(errno));
                ((t_command *)cmd_current->content)->params = alloc_params_list(token_list);
                if (!((((t_command *) cmd_current->content)->params)[params_idx++] = ft_strdup(token_list->data)))
                    exit_failure(MSH_VERSION": %s\n", strerror(errno));
				parser_state = PS_GET_PARAMS;
			}
			else if (token_list->type == TT_LEFT_AB)
				parser_state = PS_GET_STDIN;
			else if (token_list->type == TT_RIGHT_AB)
				parser_state = PS_GET_STDOUT;
			else if (token_list->type == TT_RIGHT_DAB)
				parser_state = PS_GET_STDOUT_APPEND;
			else if (token_list->type == TT_PIPE)
			{
				parser_state = PS_PARSE_ERROR;
				break ;
			}
		}

		else if (parser_state == PS_GET_PARAMS)
		{
			if (token_list->type == TT_WORD)
			{
                if (!((((t_command *) cmd_current->content)->params)[params_idx++] = ft_strdup(token_list->data)))
                    exit_failure(MSH_VERSION": %s\n", strerror(errno));
            }
			else if (token_list->type == TT_LEFT_AB)
				parser_state = PS_GET_STDIN;
			else if (token_list->type == TT_RIGHT_AB)
				parser_state = PS_GET_STDOUT;
			else if (token_list->type == TT_RIGHT_DAB)
				parser_state = PS_GET_STDOUT_APPEND;
			else if (token_list->type == TT_PIPE)
			{
				if (token_list->next->type == TT_NULL)
				{
					parser_state = PS_PARSE_ERROR;
					break ;
				}
				((t_command *)cmd_current->content)->pipe = 1;
				cmd_current->next = alloc_new_command();
				cmd_current = cmd_current->next;
				parser_state = PS_GET_NAME;
				params_idx = 0;
			}
		}

		else if (parser_state == PS_GET_STDIN)
		{
			if (token_list->type == TT_WORD)
			{
				((t_command *)cmd_current->content)->f_stdin = 1;
				if (((t_command *)cmd_current->content)->new_stdin != NULL)
					free(((t_command *)cmd_current->content)->new_stdin);
				if (!(((t_command *)cmd_current->content)->new_stdin = ft_strdup(token_list->data)))
					exit_failure(MSH_VERSION": %s\n", strerror(errno));
				if (((t_command *)cmd_current->content)->name == NULL)
					parser_state = PS_GET_NAME;
				else
					parser_state = PS_GET_PARAMS;
			}
			else if (token_list->type == TT_LEFT_AB)
				break ;
			else if (token_list->type == TT_RIGHT_AB)
				break ;
			else if (token_list->type == TT_RIGHT_DAB)
				break ;
			else if (token_list->type == TT_PIPE)
				break ;
		}

		else if (parser_state == PS_GET_STDOUT)
		{
			if (token_list->type == TT_WORD)
			{
				((t_command *)cmd_current->content)->f_stdout = 1;
				((t_command *)cmd_current->content)->f_stdout_append = 0;
				if (((t_command *)cmd_current->content)->new_stdout != NULL)
				{
					if (touch_old_stdout(cmd_current->content) != 0)
					{
						parser_clear(&cmd_list);
						return (NULL);
					}
					free(((t_command *)cmd_current->content)->new_stdout);
				}
				if (!(((t_command *)cmd_current->content)->new_stdout = ft_strdup(token_list->data)))
					exit_failure(MSH_VERSION": %s\n", strerror(errno));
				if (((t_command *)cmd_current->content)->name == NULL)
					parser_state = PS_GET_NAME;
				else
					parser_state = PS_GET_PARAMS;
			}
			else if (token_list->type == TT_LEFT_AB)
				break ;
			else if (token_list->type == TT_RIGHT_AB)
				break ;
			else if (token_list->type == TT_RIGHT_DAB)
				break ;
			else if (token_list->type == TT_PIPE)
				break ;
		}

		else if (parser_state == PS_GET_STDOUT_APPEND)
		{
			if (token_list->type == TT_WORD)
			{
				if (((t_command *)cmd_current->content)->f_stdout && \
					!ft_strcmp(((t_command *)cmd_current->content)->new_stdout, token_list->data))
						; // old stdout takes precedence over the new one if identical
				else
				{
					((t_command *)cmd_current->content)->f_stdout = 0;
					((t_command *)cmd_current->content)->f_stdout_append = 1;
					if (((t_command *)cmd_current->content)->new_stdout != NULL)
					{
						if (touch_old_stdout(cmd_current->content) != 0)
						{
							parser_clear(&cmd_list);
							return (NULL);
						}
						free(((t_command *)cmd_current->content)->new_stdout);
					}
					if (!(((t_command *)cmd_current->content)->new_stdout = ft_strdup(token_list->data)))
						exit_failure(MSH_VERSION": %s\n", strerror(errno));
				}
				if (((t_command *)cmd_current->content)->name == NULL)
					parser_state = PS_GET_NAME;
				else
					parser_state = PS_GET_PARAMS;
			}
			else if (token_list->type == TT_LEFT_AB)
				break ;
			else if (token_list->type == TT_RIGHT_AB)
				break ;
			else if (token_list->type == TT_RIGHT_DAB)
				break ;
			else if (token_list->type == TT_PIPE)
				break ;
		}

		token_list = token_list->next;
	}
	if (parser_state != PS_GET_NAME && parser_state != PS_GET_PARAMS)
	{
		ft_printf(MSH_VERSION": syntax error near unexpected token `%s'\n", \
			get_unexpected_token(token_list->type));
		parser_clear(&cmd_list);
	}
	return (cmd_list);
}
