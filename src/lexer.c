/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:23:55 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/24 12:23:05 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token				*lexer_proc(char **line)
{
	char		c;
	t_token		*tok_list;
	t_lexer		lexer;

	lexer_init(&lexer, line);
	tok_list = lexer.tok_current;
	while ((*lexer.line)[lexer.line_idx])
	{
		c = (*lexer.line)[lexer.line_idx];

		// LS_NORMAL processing.
		if (lexer.state == LS_NORMAL)
		{
			if (c == '\'' || c == '\"')
				lexer.state = (c == '\'') ? LS_IN_QUOTES : LS_IN_DQUOTES;
			else if (c == '$')
			{
				finish_current_token(&lexer);
				env_substitute(&lexer);
				continue ;
			}
			else if (c == '|')
			{
				finish_current_token(&lexer);
				lexer.tok_current->type = TT_PIPE;
				(lexer.tok_current->data)[lexer.tok_idx++] = '|';
				finish_current_token(&lexer);
			}
			else if (c == '<')
			{
				finish_current_token(&lexer);
				lexer.tok_current->type = TT_LEFT_AB;
				(lexer.tok_current->data)[lexer.tok_idx++] = '<';
				finish_current_token(&lexer);
			}
			else if (c == '>')
			{
				if (lexer.tok_current->type == TT_RIGHT_AB)
				{
					lexer.tok_current->type = TT_RIGHT_DAB;
					(lexer.tok_current->data)[lexer.tok_idx++] = '>';
					finish_current_token(&lexer);
				}
				else
				{
					finish_current_token(&lexer);
					lexer.tok_current->type = TT_RIGHT_AB;
					(lexer.tok_current->data)[lexer.tok_idx++] = '>';
				}
			}
			else if (c == ' ')
				finish_current_token(&lexer);
			else if (c == ';')
			{
				finish_current_token(&lexer);
				cut_processed_part(&lexer);
				if (tok_list->type == TT_NULL)
				{
					ft_printf(MSH_VERSION": syntax error near unexpected token `;'\n");
					lexer_clear(tok_list);
					free(*line);
					*line = NULL;
					return (NULL);
				}
				return (tok_list);
			}
			else
			{
				if (lexer.tok_current->type != TT_WORD)
					finish_current_token(&lexer);
				lexer.tok_current->type = TT_WORD;
				(lexer.tok_current->data)[lexer.tok_idx++] = c;
			}
		}

		// LS_IN_DQUOTES processing.
		else if (lexer.state == LS_IN_DQUOTES)
		{
			if (c == '\"')
				lexer.state = LS_NORMAL;
			else if (c == '$')
			{
				lexer.tok_current->type = TT_WORD;
				env_substitute(&lexer);
				continue ;
			}
			else
			{
				lexer.tok_current->type = TT_WORD;
				(lexer.tok_current->data)[lexer.tok_idx++] = c;
			}
		}

		// LS_IN_QUOTES processing.
		else if (lexer.state == LS_IN_QUOTES)
		{
			if (c == '\'')
				lexer.state = LS_NORMAL;
			else
			{
				lexer.tok_current->type = TT_WORD;
				(lexer.tok_current->data)[lexer.tok_idx++] = c;
			}
		}

		// UNKNOWN lexer state.
		else
			exit_failure(MSH_VERSION": Unknown lexer state: %c\n", (char)lexer.state);
		++lexer.line_idx;
	}
	finish_current_token(&lexer);
	free(*line);
	*line = NULL;
	return (tok_list);
}
