/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tools.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 10:13:48 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/24 10:20:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_TOOLS_H
# define TEST_TOOLS_H

# include "lexer.h"
# include "process.h"
# include "ft_stdio.h"

void			print_token_list(t_token *token_list);
void			print_command_list(t_list *command_list);

#endif
