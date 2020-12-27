/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:23:55 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/08 05:35:15 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "msh.h"
#include "lexer.h"

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

static void		finish_current_token(t_token **tok_current, int *tok_idx, size_t tok_size)
{
	((*tok_current)->data)[*tok_idx] = '\0';
	(*tok_current)->next = alloc_new_token(tok_size);
	*tok_current = (*tok_current)->next;
	*tok_idx = 0;
}

static void		env_substitute(t_token *tok_current, int *tok_idx, size_t tok_size)
{
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
	**token_list = NULL;
}

t_token		*lexer_proc(char *line)
{
	int			lexer_state;
	int			tok_idx;
	size_t		tok_size;
	char		c;
	char		*env_buffer;
	t_token		*tok_list;
	t_token		*tok_current;

	lexer_state = LS_NORMAL;
	tok_size = ft_strlen(line) + 1;
	tok_list = alloc_new_token(tok_size);
	tok_current = tok_list;
	tok_idx = 0;
	if (!(env_buffer = malloc(tok_size)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	*env_buffer = '\0';
	while (*line)
	{
		c = *line++;
		if (lexer_state == LS_NORMAL)
		{
		}


		else if (lexer_state == LS_IN_DQUOTES)
		{
			if (c == '\"')
			{
				lexer_state = LS_NORMAL;
				if (tok_current->type != TT_NULL)
					finish_current_token(&tok_current, &tok_idx, tok_size);
			}
			else if (c == '$')
				env_substitute(tok_current, &tok_idx, tok_size);
			else
			{
				(tok_current->data)[tok_idx++] = c;
				if (tok_current->type == TT_NULL)
					tok_current->type = TT_WORD;
			}
		}


		else if (lexer_state == LS_IN_QUOTES)
		{
			if (c == '\'')
			{
				lexer_state = LS_NORMAL;
				if (tok_current->type != TT_NULL)
					finish_current_token(&tok_current, &tok_idx, tok_size);
			}
			else
			{
				(tok_current->data)[tok_idx++] = c;
				if (tok_current->type == TT_NULL)
					tok_current->type = TT_WORD;
			}
		}
	}
}
