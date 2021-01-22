/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:13:09 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/22 13:30:19 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "ft_list.h"
# include "lexer.h"

enum			e_parser_states
{
	PS_GET_NAME,
	PS_GET_PARAMS,
	PS_GET_STDIN,
	PS_GET_STDOUT,
	PS_GET_STDOUT_APPEND,
	PS_PARSE_ERROR
};

t_list			*parser_proc(t_token *token_list);
void			parser_clear(t_list **command_list);

#endif
