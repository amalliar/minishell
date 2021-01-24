/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:20:29 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/24 16:51:35 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void		append_tokens(t_lexer *lexer, char **word_list)
{
	if (lexer->tok_current->type == TT_NULL && *word_list)
	{
		free(lexer->tok_current->data);
		if (!(lexer->tok_current->data = ft_strdup(*word_list++)))
			exit_failure(MSH_VERSION": %s\n", strerror(errno));
		lexer->tok_current->type = TT_WORD;
	}
	while (*word_list)
	{
		lexer->tok_size = ft_strlen(*word_list) + 1;
		lexer->tok_current->next = alloc_new_token(lexer->tok_size);
		lexer->tok_current = lexer->tok_current->next;
		ft_memcpy(lexer->tok_current->data, *word_list++, lexer->tok_size);
		lexer->tok_current->type = TT_WORD;
	}
	if (lexer->tok_current->type != TT_NULL)
	{
		lexer->tok_current->next = \
			alloc_new_token(ft_strlen(*lexer->line - lexer->line_idx));
		lexer->tok_current = lexer->tok_current->next;
	}
	lexer->tok_idx = 0;
}

static void		expand_token(t_lexer *lexer, char *word)
{
	char	*buff;
	int		buff_size;
	int		word_len;

	if (!word)
		exit_failure(MSH_VERSION": expand_token() got a NULL pointer.\n");
	word_len = ft_strlen(word);
	buff_size = ft_strlen(*lexer->line) + lexer->tok_idx + word_len + 1;
	if (!(buff = malloc(buff_size)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	ft_memcpy(buff, lexer->tok_current->data, lexer->tok_idx);
	ft_memcpy(buff + lexer->tok_idx, word, word_len);
	free(lexer->tok_current->data);
	lexer->tok_current->data = buff;
	lexer->tok_idx += word_len;
}

static char		*get_evar_name(t_lexer *lexer)
{
	char	c;
	char	*evar;
	int		evar_size;
	int		evar_idx;

	++lexer->line_idx;
	evar_size = ft_strlen(*lexer->line) + lexer->line_idx + 1;
	if (!(evar = malloc(evar_size)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	evar_idx = 0;
	while (1)
	{
		c = (*lexer->line)[lexer->line_idx];
		if (ft_strchr(" ;|<>$\"\'", c) || (evar_idx == 1 && evar[0] == '?'))
		{
			evar[evar_idx] = '\0';
			break ;
		}
		evar[evar_idx++] = c;
		++lexer->line_idx;
	}
	return (evar);
}

void			env_substitute(t_lexer *lexer)
{
	char	*evar;
	char	*eval;
	char	*ifs;
	char	**tokens;

	evar = get_evar_name(lexer);
	if ((eval = ft_getenv(evar)))
	{
		if (lexer->state == LS_NORMAL)
		{
			if (!(ifs = ft_getenv("IFS")))
				ifs = " \t\n";
			if (!(tokens = ft_split(eval, ifs)))
				exit_failure(MSH_VERSION": %s\n", strerror(errno));
			append_tokens(lexer, tokens);
			strarr_free(tokens);
		}
		else
			expand_token(lexer, eval);
	}
	free(evar);
	--lexer->line_idx;
}
