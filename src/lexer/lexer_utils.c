/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:13:29 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 11:25:15 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			lexer_init(t_lexer *lexer, char **line)
{
	if (!line || !*line)
		exit_failure(MSH_VERSION": lexer_proc() got a NULL pointer.\n");
	lexer->tok_size = ft_strlen(*line) + 1;
	lexer->tok_current = alloc_new_token(lexer->tok_size);
	lexer->tok_idx = 0;
	lexer->line_idx = 0;
	lexer->line = line;
	lexer->state = LS_NORMAL;
}

t_token			*alloc_new_token(size_t size)
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

void			finish_current_token(t_lexer *lexer)
{
	if (lexer->tok_current->type != TT_NULL)
	{
		(lexer->tok_current->data)[lexer->tok_idx] = '\0';
		lexer->tok_current->next = alloc_new_token(lexer->tok_size);
		lexer->tok_current = lexer->tok_current->next;
	}
	lexer->tok_idx = 0;
}

void			cut_processed_part(t_lexer *lexer)
{
	char	*remainder;

	if (!lexer->line || !*lexer->line)
		exit_failure(MSH_VERSION": cut_processed_part() got a NULL pointer.\n");
	if (!(remainder = ft_strdup(*lexer->line + lexer->line_idx + 1)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	free(*lexer->line);
	*lexer->line = remainder;
}

void			lexer_clear(t_token *token_list)
{
	t_token		*tmp;

	while (token_list)
	{
		tmp = token_list;
		token_list = token_list->next;
		free(tmp->data);
		free(tmp);
	}
}
