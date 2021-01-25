/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:25:05 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/25 12:25:32 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				touch_old_stdout(t_command *cmd)
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
