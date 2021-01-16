/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:23:55 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/16 07:04:51 by amalliar         ###   ########.fr       */
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

static void		append_tokens(t_token **tok_current, char **word_list)
{
	t_token		*temp_tok;
	int			tok_size;


	if (!tok_current || !*tok_current || !word_list || !*word_list)
		exit_failure(MSH_VERSION": append_tokens() got a NULL pointer.\n");
	temp_tok = *tok_current;
	while (*word_list)
	{
		tok_size = ft_strlen(*word_list);
		temp_tok->next = alloc_new_token(tok_size);
		temp_tok = temp_tok->next;
		temp_tok->data = *word_list;
		++word_list;
	}
	*tok_current = temp_tok;
}

static void		expand_token(t_token *tok_current, int *tok_idx, char *word)
{
	char	*buff;
	int		buff_size;
	int		word_size;

	if (!tok_current || !word)
		exit_failure(MSH_VERSION": expand_token() got a NULL pointer.\n");
	word_size = ft_strlen(word);
	buff_size = ft_strlen(tok_current->data) + word_size;
	if (!(buff = malloc(buff_size)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	ft_memcpy(buff, tok_current->data, *tok_idx);
	ft_memcpy(buff + *tok_idx, word, word_size);
	free(tok_current->data);
	tok_current->data = buff;
	*tok_idx += word_size;
}

void		env_substitute(t_token **tok_current, int *tok_idx, char *line, int *line_idx, int lexer_state)
{
	char	c;
	char	*evar;
	char	*eval;
	char	**tokens;
	char	*ifs;
	int		evar_size;
	int		evar_idx;

	if (!tok_current || !*tok_current || !line || !line_idx)
		exit_failure(MSH_VERSION": env_substitute() got a NULL pointer.\n");
	evar_size = ft_strlen(line + line_idx + 1);
	if (!(evar = malloc(evar_size)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	evar_idx = 0;
	if (!(ifs = ft_getenv("IFS")))
		ifs = " \t\n";
	while ((c = line[*line_idx]))
	{
		++*line_idx;
		if (c == '$' || ft_strchr(ifs, c) || (lexer_state == LS_NORMAL && ft_strchr(";|<>", c)))
		{
			evar[evar_idx] = '\0';
			break ;
		}
		evar[evar_idx++] = c;
	}
	if ((eval = ft_getenv(evar)))
	{
		if (lexer_state == LS_NORMAL)
		{
			if (!(tokens = ft_split(eval, ifs)))
				exit_failure(MSH_VERSION": %s\n", strerror(errno));
			append_tokens(tok_current, tokens);
			strarr_free(tokens);
		}
		else
			expand_token(*tok_current, tok_idx, eval);
		free(eval);
	}
	free(evar);
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
		exit_failure(MSH_VERSION": lexer_proc() got a NULL pointer.\n");
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
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
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
				env_substitute(&tok_current, &tok_idx, *line, &line_idx, lexer_state);
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
