/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:23:55 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/24 15:39:31 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void			proc_ls_normal(t_lexer *lexer, t_token **tok_list, char c)
{
	if (c == '$')
	{
		finish_current_token(lexer);
		env_substitute(lexer);
	}
	else if (c == '|' || c == '<')
	{
		finish_current_token(lexer);
		lexer->tok_current->type = c;
		(lexer->tok_current->data)[lexer->tok_idx++] = c;
		finish_current_token(lexer);
	}
	else if (c == '>' && lexer->tok_current->type == TT_RIGHT_AB)
	{
		lexer->tok_current->type = TT_RIGHT_DAB;
		(lexer->tok_current->data)[lexer->tok_idx++] = '>';
		finish_current_token(lexer);
	}
	else
		proc_ls_normal_2(lexer, tok_list, c);
}

static void			proc_ls_in_dquotes(t_lexer *lexer, char c)
{
	if (c == '\"')
		lexer->state = LS_NORMAL;
	else if (c == '$')
	{
		lexer->tok_current->type = TT_WORD;
		env_substitute(lexer);
	}
	else
	{
		lexer->tok_current->type = TT_WORD;
		(lexer->tok_current->data)[lexer->tok_idx++] = c;
	}
}

static void			proc_ls_in_quotes(t_lexer *lexer, char c)
{
	if (c == '\'')
		lexer->state = LS_NORMAL;
	else
	{
		lexer->tok_current->type = TT_WORD;
		(lexer->tok_current->data)[lexer->tok_idx++] = c;
	}
}

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
		if (lexer.state == LS_NORMAL)
			proc_ls_normal(&lexer, &tok_list, c);
		else if (lexer.state == LS_IN_DQUOTES)
			proc_ls_in_dquotes(&lexer, c);
		else if (lexer.state == LS_IN_QUOTES)
			proc_ls_in_quotes(&lexer, c);
		else if (lexer.state == LS_RETURN_RES)
			return (tok_list);
		++lexer.line_idx;
	}
	finish_current_token(&lexer);
	free(*line);
	*line = NULL;
	return (tok_list);
}
