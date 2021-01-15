/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:23:55 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/15 06:22:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include "msh.h"
#include "lexer.h"
#include "ft_string.h"
#include "ft_ctype.h"

static t_token		*alloc_new_token(size_t size)
{
	t_token		*token;

	if (!(token = malloc(sizeof(t_token))) || \
		!(token->data = malloc(size)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	*(token->data) = '\0';
	token->type = TT_NULL;
	token->next = NULL;
	return (token);
}

static void		finish_current_token(t_token **tok_current, int *tok_idx, int tok_size)
{
	if ((*tok_current)->type == TT_NULL)
		return ;
	((*tok_current)->data)[*tok_idx] = '\0';
	(*tok_current)->next = alloc_new_token(tok_size);
	*tok_current = (*tok_current)->next;
	*tok_idx = 0;
}

void		lexer_clear(t_token **token_list)
{
	t_token		*current_tok;
	t_token		*tmp;

	current_tok = *token_list;
	while (current_tok)
	{
		free(current_tok->data);
		tmp = current_tok;
		current_tok = current_tok->next;
		free(tmp);
	}
	*token_list = NULL;
}

void		cut_processed_part(char **line, int line_idx)
{
	char	*remainder;

	if (!(remainder = ft_strdup(*line + line_idx)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	free(*line);
	*line = remainder;
}

void		env_substitute(t_token **tok_current, int *tok_idx, char *line, int *line_idx, int lexer_state)
{
	int		tok_size;
	int		var_idx;
	char	*var;
	char	*value;

	tok_size = ft_strlen(line + *line_idx);
	var_idx = 0;
	if (!(var = malloc(tok_size + 1)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	while (*line && !ft_isspace(line[*line_idx]) || (lexer_state == LS_NORMAL && ft_strchr("$;|<>", line[*line_idx])))
	{
		var[var_idx++] = line[*line_idx];
		++*line_idx;
	}
	var[var_idx] = '\0';

	/*
	value = get_env(var);
	if (value)
	{
		if (lexer_state == LS_NORMAL)
		{
			finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
			append_tokens_from_string(tok_current, value);
		}
		else
		{

		}
	}
	free(value);
	*/
	free(var);
}

t_token		*lexer_proc(char **line)
{
	int			lexer_state;
	int			tok_idx;
	int			line_idx;
	int			tok_size;
	char		c;
	t_token		*tok_list;
	t_token		*tok_current;

	if (!line)
		exit_failure(MSH_VERSION": lexer input line is NULL\n");
	lexer_state = LS_NORMAL;
	tok_size = ft_strlen(*line) + 1;
	tok_list = alloc_new_token(tok_size);
	tok_current = tok_list;
	tok_idx = 0;
	line_idx = 0;
	while (1)
	{
		c = (*line)[line_idx++];

		// LS_NORMAL processing.
		if (lexer_state == LS_NORMAL)
		{
			if (c == '\'')
			{
				lexer_state = LS_IN_QUOTES;
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
			}
			else if (c == '\"')
			{
				lexer_state = LS_IN_DQUOTES;
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
			}
			else if (c == '$')
			{
				env_substitute(&tok_current, &tok_idx, *line, &line_idx, lexer_state);
			}
			else if (c == '|')
			{
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				tok_current->type = TT_PIPE;
				*(tok_current->data) = '|';
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
			}
			else if (c == '<')
			{
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				tok_current->type = TT_LEFT_AB;
				*(tok_current->data) = '<';
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
			}
			else if (c == '>')
			{
				if (tok_current->type == TT_RIGHT_AB)
					tok_current->type = TT_RIGHT_DAB;
				else
				{
					finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
					tok_current->type = TT_RIGHT_AB;
				}
				(tok_current->data)[tok_idx++] = '>';
			}
			else if (ft_isspace(c) || c == '\0')
			{
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
			}
			else if (c == ';')
			{
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				cut_processed_part(line, line_idx);
				return (tok_list);
			}
			else
			{
				(tok_current->data)[tok_idx++] = c;
			}
		}
		// LS_IN_DQUOTES processing.
		else if (lexer_state == LS_IN_DQUOTES)
		{
			if (c == '\"' || c == '\0')
			{
				lexer_state = LS_NORMAL;
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				tok_idx = 0;
			}
			else if (c == '$')
			{
				env_substitute(&tok_current, &tok_idx, *line, &line_idx, lexer_state);
			}
			else
			{
				(tok_current->data)[tok_idx++] = c;
			}
		}
		// LS_IN_QUOTES processing.
		else if (lexer_state == LS_IN_QUOTES)
		{
			if (c == '\'' || c == '\0')
			{
				lexer_state = LS_NORMAL;
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				tok_idx = 0;
			}
			else
			{
				(tok_current->data)[tok_idx++] = c;
			}
		}
		// UNKNOWN lexer state.
		else
			exit_failure(MSH_VERSION": Unknown lexer state: %c\n", (char)lexer_state);
	}
	return (tok_list);
}
