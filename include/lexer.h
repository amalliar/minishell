/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:29:18 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/24 12:37:09 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#include "msh.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include "env_tools.h"
#include "error_tools.h"
#include "other_tools.h"

enum					e_lexer_states
{
	LS_NORMAL,
	LS_IN_QUOTES,
	LS_IN_DQUOTES,
};

enum					e_token_types
{
	TT_PIPE = '|',
	TT_LEFT_AB = '<',
	TT_RIGHT_AB = '>',
	TT_RIGHT_DAB,
	TT_WORD,
	TT_NULL = 0
};

typedef struct			s_token
{
	char				*data;
	int					type;
	struct s_token		*next;
}						t_token;

typedef struct			s_lexer
{
	int					state;
	int					line_idx;
	int					tok_idx;
	int					tok_size;
	t_token				*tok_current;
	char				**line;
}						t_lexer;

t_token					*alloc_new_token(size_t size);
t_token					*lexer_proc(char **line);
void					lexer_init(t_lexer *lexer, char **line);
void					lexer_clear(t_token *token_list);
void					finish_current_token(t_lexer *lexer);
void					cut_processed_part(t_lexer *lexer);
void					env_substitute(t_lexer *lexer);

#endif
