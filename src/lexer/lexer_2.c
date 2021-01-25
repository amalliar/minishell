/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:36:30 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 12:53:02 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			proc_ls_normal_2(t_lexer *lexer, t_token **tok_list, char c)
{
	if (c == '>')
	{
		finish_current_token(lexer);
		lexer->tok_current->type = TT_RIGHT_AB;
		(lexer->tok_current->data)[lexer->tok_idx++] = '>';
	}
	else if (c == ';')
	{
		finish_current_token(lexer);
		cut_processed_part(lexer);
		if ((*tok_list)->type == TT_NULL)
		{
			ft_printf(MSH_VERSION": syntax error near unexpected token `;'\n");
			lexer_clear(*tok_list);
			*tok_list = NULL;
			free(*lexer->line);
			*lexer->line = NULL;
		}
		lexer->state = LS_RETURN_RES;
	}
	else
		proc_ls_normal_3(lexer, c);
}

void			proc_ls_normal_3(t_lexer *lexer, char c)
{
	if (c == '\'' || c == '\"')
	{
		lexer->state = (c == '\'') ? LS_IN_QUOTES : LS_IN_DQUOTES;
		if (lexer->tok_current->type != TT_WORD)
			finish_current_token(lexer);
	}
	else if (c == ' ')
		finish_current_token(lexer);
	else if (c == '\\')
		(lexer->tok_current->data)[lexer->tok_idx++] = \
			(*lexer->line)[++lexer->line_idx];
	else
	{
		if (lexer->tok_current->type != TT_WORD)
			finish_current_token(lexer);
		lexer->tok_current->type = TT_WORD;
		(lexer->tok_current->data)[lexer->tok_idx++] = c;
	}
}
