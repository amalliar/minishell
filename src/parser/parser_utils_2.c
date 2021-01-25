/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:25:05 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 18:36:15 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				touch_new_stdout(t_command *cmd)
{
	int		flag;
	int		fd;

	flag = (cmd->f_stdout_append) ? O_APPEND : O_TRUNC;
	if ((fd = open(cmd->new_stdout, O_WRONLY | O_CREAT | flag, 0664)) == -1)
	{
		ft_printf(MSH_VERSION": %s: %s\n", cmd->new_stdout, strerror(errno));
		return (1);
	}
	close(fd);
	return (0);
}

void			parser_init(t_parser *parser, t_token *token_list)
{
	parser->state = PS_GET_NAME;
	parser->params_idx = 0;
	parser->cmd_current = alloc_new_command();
	parser->cmd_list = parser->cmd_current;
	parser->tok_current = token_list;
}
