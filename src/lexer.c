/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:23:55 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/22 14:40:50 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#include "msh.h"
#include "lexer.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include "env_tools.h"
#include "error_tools.h"
#include "other_tools.h"

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

static void			finish_current_token(t_token **tok_current, int *tok_idx, \
						int tok_size)
{
	if ((*tok_current)->type == TT_NULL)
		return ;
	((*tok_current)->data)[*tok_idx] = '\0';
	(*tok_current)->next = alloc_new_token(tok_size);
	*tok_current = (*tok_current)->next;
	*tok_idx = 0;
}

void				lexer_clear(t_token *token_list)
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

void				cut_processed_part(char **line, int line_idx)
{
	char	*remainder;

	if (!line || !*line)
		exit_failure(MSH_VERSION": cut_processed_part() got a NULL pointer.\n");
	if (!(remainder = ft_strdup(*line + line_idx + 1)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	free(*line);
	*line = remainder;
}

static void			append_tokens(t_token **tok_current, int *tok_idx, int tok_size, char **word_list)
{
	t_token		*temp_tok;
	int			temp_tok_size;

	if (!tok_current || !*tok_current || !word_list)
		exit_failure(MSH_VERSION": append_tokens() got a NULL pointer.\n");
	temp_tok = *tok_current;
	if (temp_tok->type == TT_NULL && *word_list)
	{
		free(temp_tok->data);
		if (!(temp_tok->data = ft_strdup(*word_list++)))
			exit_failure(MSH_VERSION": %s\n", strerror(errno));
		temp_tok->type = TT_WORD;
	}
	while (*word_list)
	{
		temp_tok_size = ft_strlen(*word_list) + 1;
		temp_tok->next = alloc_new_token(temp_tok_size);
		temp_tok = temp_tok->next;
		ft_memcpy(temp_tok->data, *word_list, temp_tok_size);
		temp_tok->type = TT_WORD;
	}
	if (temp_tok->type != TT_NULL)
	{
		temp_tok->next = alloc_new_token(tok_size);
		temp_tok = temp_tok->next;
	}
	*tok_current = temp_tok;
	*tok_idx = 0;
}

static void			expand_token(t_token *tok_current, int *tok_idx, int tok_size, char *word)
{
	char	*buff;
	int		buff_size;
	int		word_len;

	if (!tok_current || !word)
		exit_failure(MSH_VERSION": expand_token() got a NULL pointer.\n");
	word_len = ft_strlen(word);
	if (!(buff = malloc(tok_size + *tok_idx + word_len)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	ft_memcpy(buff, tok_current->data, *tok_idx);
	ft_memcpy(buff + *tok_idx, word, word_len);
	free(tok_current->data);
	tok_current->data = buff;
	*tok_idx += word_len;
}

void				env_substitute(t_token **tok_current, int *tok_idx, char *line, int *line_idx, int lexer_state)
{
	char	c;
	char	*evar;
	char	*eval;
	char	*ifs;
	char	**tokens;
	int		evar_size;
	int		evar_idx;

	if (!tok_current || !*tok_current || !line || !line_idx)
		exit_failure(MSH_VERSION": env_substitute() got a NULL pointer.\n");
	++*line_idx;
	evar_size = ft_strlen(line + *line_idx + 1);
	if (!(evar = malloc(evar_size)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	evar_idx = 0;
	while (1)
	{
		c = line[*line_idx];
		if (ft_strchr(" ;|<>$\"\'", c))
		{
			evar[evar_idx] = '\0';
			break ;
		}
		evar[evar_idx++] = c;
		++*line_idx;
	}
	if ((eval = ft_getenv(evar)))
	{
		if (lexer_state == LS_NORMAL)
		{
			if (!(ifs = ft_getenv("IFS")))
				ifs = " \t\n";
			if (!(tokens = ft_split(eval, ifs)))
				exit_failure(MSH_VERSION": %s\n", strerror(errno));
			append_tokens(tok_current, tok_idx, ft_strlen(line) - *line_idx, tokens);
			strarr_free(tokens);
		}
		else
			expand_token(*tok_current, tok_idx, ft_strlen(line) + 1, eval);
	}
	free(evar);
}

t_token				*lexer_proc(char **line)
{
	int			lexer_state;
	int			line_idx;
	int			tok_idx;
	int			tok_size;
	char		c;
	t_token		*tok_list;
	t_token		*tok_current;

	if (!line)
		exit_failure(MSH_VERSION": lexer_proc() got a NULL pointer.\n");
	tok_size = ft_strlen(*line) + 1;
	tok_list = alloc_new_token(tok_size);
	tok_current = tok_list;
	tok_idx = 0;
	line_idx = 0;
	lexer_state = LS_NORMAL;
	while ((*line)[line_idx])
	{
		c = (*line)[line_idx];

		// LS_NORMAL processing.
		if (lexer_state == LS_NORMAL)
		{
			if (c == '\'' || c == '\"')
			{
				lexer_state = (c == '\'') ? LS_IN_QUOTES : LS_IN_DQUOTES;
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
			}
			else if (c == '$')
			{
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				env_substitute(&tok_current, &tok_idx, *line, &line_idx, lexer_state);
				continue ;
			}
			else if (c == '|')
			{
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				tok_current->type = TT_PIPE;
				(tok_current->data)[tok_idx++] = '|';
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
			}
			else if (c == '<')
			{
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				tok_current->type = TT_LEFT_AB;
				(tok_current->data)[tok_idx++] = '<';
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
			}
			else if (c == '>')
			{
				if (tok_current->type == TT_RIGHT_AB)
				{
					tok_current->type = TT_RIGHT_DAB;
					(tok_current->data)[tok_idx++] = '>';
					finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				}
				else
				{
					finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
					tok_current->type = TT_RIGHT_AB;
					(tok_current->data)[tok_idx++] = '>';
				}
			}
			else if (c == ' ')
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
			else if (c == ';')
			{
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				cut_processed_part(line, line_idx);
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
				if (tok_current->type != TT_WORD)
					finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				tok_current->type = TT_WORD;
				(tok_current->data)[tok_idx++] = c;
			}
		}

		// LS_IN_DQUOTES processing.
		else if (lexer_state == LS_IN_DQUOTES)
		{
			if (c == '\"')
			{
				lexer_state = LS_NORMAL;
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				tok_idx = 0;
			}
			else if (c == '$')
			{
				env_substitute(&tok_current, &tok_idx, *line, &line_idx, lexer_state);
				continue ;
			}
			else
			{
				tok_current->type = TT_WORD;
				(tok_current->data)[tok_idx++] = c;
			}
		}

		// LS_IN_QUOTES processing.
		else if (lexer_state == LS_IN_QUOTES)
		{
			if (c == '\'')
			{
				lexer_state = LS_NORMAL;
				finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
				tok_idx = 0;
			}
			else
			{
				tok_current->type = TT_WORD;
				(tok_current->data)[tok_idx++] = c;
			}
		}

		// UNKNOWN lexer state.
		else
			exit_failure(MSH_VERSION": Unknown lexer state: %c\n", (char)lexer_state);
		++line_idx;
	}
	finish_current_token(&tok_current, &tok_idx, tok_size - line_idx);
	free(*line);
	*line = NULL;
	return (tok_list);
}
